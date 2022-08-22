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


void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value)
{
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // node full
        printf("Need to implement splitting a leaf node.\n");
        exit(-1);
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

#endif  // SIMPLEDB_TABLE_H_
