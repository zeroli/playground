#ifndef SIMPLEDB_TABLE_H_
#define SIMPLEDB_TABLE_H_

#include <cstdint>

#include "pager.h"
#include "cursor.h"
#include "row.h"
#include "btree.h"

struct Table {
    Pager* pager;
    uint32_t num_rows;
    uint32_t root_page_num;  // root page number in btree
};

void create_new_root(Table* table, uint32_t right_child_page_num)
{
    /*
    handle splitting the root
    old root copied to new page, becomes left child.
    address of right child passed in.
    re-initialize root page to contain the new root node.
    New root node points to two children
    */
   void* root = get_page(table->pager, table->root_page_num);
   void* right_child = get_page(table->pager, right_child_page_num);
   uint32_t left_child_page_num = get_unused_page_num(table->pager);
   void* left_child = get_page(table->pager, left_child_page_num);

   memcpy(left_child, root, PAGE_SIZE);
   set_node_root(left_child, false);

   // root node is a new internal node with one key and two children
   initialize_internal_node(root);
   set_node_root(root, true);
   *internal_node_num_keys(root) = 1;
   *internal_node_child(root, 0) = left_child_page_num;
   uint32_t left_child_max_key = get_node_max_key(left_child);
   *internal_node_key(root, 0) = left_child_max_key;
   *internal_node_right_child(root) = right_child_page_num;
}

void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value)
{
    /*
    Create a  new node and move half the cell over.
    Insert the new value in one of the two nodes.
    update parent or create a new parent
    */
    void* old_node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t new_page_num = get_unused_page_num(cursor->table->pager);
    void* new_node = get_page(cursor->table->pager, new_page_num);
    initialize_leaf_node(new_node);

    /*
    All existing keys plus new key should be divided
    evenly between old(left) and new(right) nodes.
    starting from the right, move each key to correct position
    */
    for (int32_t i = LEAF_NODE_MAX_CELLS; i >= 0; i--) {
        void* destination_node;
        if (i >= LEAF_NODE_LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }

        uint32_t index_within_node = i % LEAF_NODE_LEFT_SPLIT_COUNT;
        void* destination = leaf_node_cell(destination_node, index_within_node);

        if (i == cursor->cell_num) {
            serialize_row(value, destination);
        } else if (i > cursor->cell_num) {
            memcpy(destination, leaf_node_cell(old_node, i - 1), LEAF_NODE_CELL_SIZE);
        } else {
            memcpy(destination, leaf_node_cell(old_node, i), LEAF_NODE_CELL_SIZE);
        }
    }

    *(leaf_node_num_cells(old_node)) = LEAF_NODE_LEFT_SPLIT_COUNT;
    *(leaf_node_num_cells(new_node)) = LEAF_NODE_RIGHT_SPLIT_COUNT;

    if (is_node_root(old_node)) {
        return create_new_root(cursor->table, new_page_num);
    } else {
        printf("Need to implement updating parent after split\n");
        exit(-1);
    }
}

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value)
{
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // node full
        leaf_node_split_and_insert(cursor, key, value);
        return;
    }

    if (cursor->cell_num < num_cells) {
        // make room for new cell
        for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
            memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1), LEAF_NODE_CELL_SIZE);
        }
    }

    *(leaf_node_num_cells(node)) += 1;
    *(leaf_node_key(node, cursor->cell_num)) = key;
    serialize_row(value, leaf_node_value(node, cursor->cell_num));
}

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key)
{
    void* node = get_page(table->pager, page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);

    Cursor* cursor = new Cursor;
    cursor->table = table;
    cursor->page_num = page_num;

    // binary search
    uint32_t min_index = 0;
    uint32_t one_past_max_index = num_cells;
    while (one_past_max_index != min_index) {
        uint32_t index = (min_index + one_past_max_index) / 2;
        uint32_t key_at_index = *leaf_node_key(node, index);
        if (key == key_at_index) {
            cursor->cell_num = index;
            return cursor;
        }
        if (key < key_at_index) {
            one_past_max_index = index;
        } else {
            min_index = index + 1;
        }
    }

    cursor->cell_num = min_index;
    return cursor;
}

void* cursor_value(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* page = get_page(cursor->table->pager, page_num);

    return leaf_node_value(page, cursor->cell_num);
}

void cursor_advance(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* node = get_page(cursor->table->pager, page_num);

    cursor->cell_num += 1;
    if (cursor->cell_num >= *leaf_node_num_cells(node)) {
        cursor->end_of_table = true;
    }
}

Cursor* table_start(Table* table)
{
    Cursor* cursor = new Cursor;
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->end_of_table = (num_cells == 0);
    return cursor;
}

/*
 return the position of the given key
 if the key is not present, return the position
 where it should be inserted
*/
Cursor* table_find(Table* table, uint32_t key)
{
    uint32_t root_page_num = table->root_page_num;
    void* root_node = get_page(table->pager, table->root_page_num);
    if (get_node_type(root_node) == NODE_LEAF) {
        return leaf_node_find(table, root_page_num, key);
    } else {
        printf("Need to implement searching an internal node\n");
        exit(-1);
    }
}

Table* db_open(const char* filename)
{
    Pager* pager = pager_open(filename);

    Table* table = new Table;
    table->pager = pager;
    table->root_page_num = 0;

    if (pager->num_pages == 0) {
        // new database file. initialize page 0 as leaf node
        void* root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
        set_node_root(root_node, true);
    }

    return table;
}

void db_close(Table* table)
{
    Pager* pager = table->pager;

    for (uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }
        pager_flush(pager, i);
        delete [] (char*)pager->pages[i];
        pager->pages[i] = NULL;
    }

    int result = fclose(pager->fp);
    if (result == -1) {
        printf("Error closing db file.\n");
        exit(-1);
    }
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void* page = pager->pages[i];
        if (page) {
            delete [] (char*)page;
            pager->pages[i] = NULL;
        }
    }
    delete pager;
    delete table;
}

void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level)
{
    void* node = get_page(pager, page_num);
    uint32_t num_keys, child;

    switch (get_node_type(node)) {
        case NODE_LEAF:
            num_keys = *leaf_node_num_cells(node);
            indent(indentation_level);
            printf("- leaf (size %d)\n", num_keys);
            for (uint32_t i = 0; i < num_keys; i++) {
                indent(indentation_level + 1);
                printf("- %d\n", *leaf_node_key(node, i));
            }
            break;
        case NODE_INTERNAL:
            num_keys = *internal_node_num_keys(node);
            indent(indentation_level);
            printf("- internal (size %d)\n", num_keys);
            for (uint32_t i = 0; i < num_keys; i++) {
                child = *internal_node_child(node, i);
                print_tree(pager, child, indentation_level + 1);

                indent(indentation_level + 1);
                printf("- key %d\n", *internal_node_key(node, i));
            }
            child = *internal_node_right_child(node);
            print_tree(pager, child, indentation_level + 1);
            break;
    }
}

#endif  // SIMPLEDB_TABLE_H_
