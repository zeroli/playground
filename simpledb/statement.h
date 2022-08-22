#ifndef SIMPLEDB_STATEMENT_H_
#define SIMPLEDB_STATEMENT_H_

#include "row.h"

enum StatementType {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
};

struct Statement {
    StatementType type;
    Row row_to_insert;  // only used by insertion
};

#endif  // SIMPLEDB_STATEMENT_H_
