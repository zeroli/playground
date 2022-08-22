#ifndef SIMPLEDB_VM_H_
#define SIMPLEDB_VM_H_

#include "table.h"
#include "statement.h"

enum ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
};

ExecuteResult execute_insert(Statement* statement, Table* table)
{
    void* node = get_page(table->pager, table->root_page_num);
    if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)) {
        return EXECUTE_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->row_to_insert);
    Cursor* cursor = table_end(table);
    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);
    delete cursor;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
    Cursor* cursor = table_start(table);
    Row row;
    while (!(cursor->end_of_table)) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    delete cursor;
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table)
{
    switch (statement->type) {
        case STATEMENT_INSERT:
            return execute_insert(statement, table);
        case STATEMENT_SELECT:
            return execute_select(statement, table);
        default:
            assert(0);
    }
}

#endif  // SIMPLEDB_VM_H_
