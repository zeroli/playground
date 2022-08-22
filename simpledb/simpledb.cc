#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include "pager.h"
#include "table.h"
#include "inputbuffer.h"
#include "prepare.h"
#include "statement.h"
#include "vm.h"
#include "metacommand.h"

void print_prompt()
{
    printf("db > ");
}

int main(int argc, char** argv)
{
    const char* filename = "test.db";
    if (argc < 2) {
        printf("No database filename provided, use test.db.\n");
    } else {
        filename = argv[1];
    }
    printf("database filename: %s\n", filename);

    Table* table = db_open(filename);

    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer, table)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer.c_str());
                    continue;
            }
        }
        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. could not parse statement.\n");
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%'.\n",
                    input_buffer->buffer.c_str());
                continue;
        }
        switch (execute_statement(&statement, table)) {
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Error: Table full.\n");
                break;
        }
    }
    return 0;
}
