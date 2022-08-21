#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

struct InputBuffer {
    std::string buffer;
};

enum MetaCommandResult {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
};

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
};

enum StatementType {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
};

struct Statement {
    StatementType type;
};

InputBuffer* new_input_buffer()
{
    InputBuffer* input_buffer = new InputBuffer;
    return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer)
{
    delete input_buffer;
}

void print_prompt()
{
    printf("db > ");
}

void read_input(InputBuffer* input_buffer)
{
    std::getline(std::cin, input_buffer->buffer);
    if (input_buffer->buffer.empty()) {
        printf("Error reading input\n");
        exit(-1);
    }
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
    if (input_buffer->buffer == ".exit") {
        close_input_buffer(input_buffer);
        exit(0);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer.c_str(), "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer.c_str(), "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement)
{
    switch (statement->type) {
        case STATEMENT_INSERT:
            printf("This is wher we would do an insert.\n");
            break;
        case STATEMENT_SELECT:
            printf("This is where we would do a select.\n");
            break;
        default:
            assert(0);
    }
}

int main(int argc, char** argv)
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
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
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%'.\n",
                    input_buffer->buffer.c_str());
                continue;
        }
        execute_statement(&statement);
        printf("Executed.\n");
    }
}
