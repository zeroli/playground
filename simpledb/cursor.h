#ifndef SIMPLEDB_CURSOR_H_
#define SIMPLEDB_CURSOR_H_

#include <cstdint>

struct Table;

struct Cursor {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;  // page里面的第几个k/v pair
    bool end_of_table;  // indicates a position one past the last element
};

#endif  // SIMPLEDB_CURSOR_H_
