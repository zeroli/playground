#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
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
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
};

enum ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
};

enum StatementType {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
};

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

struct Row {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
};

#define size_of_attribute(Struct, Attribute) \
    sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

struct Table {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
};

struct Statement {
    StatementType type;
    Row row_to_insert;  // only used by insertion
};

void print_row(Row* row)
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

void serialize_row(Row* source, void* destination)
{
    memcpy((char*)destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy((char*)destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy((char*)destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination)
{
    memcpy(&(destination->id), (char*)source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), (char*)source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), (char*)source + EMAIL_OFFSET, EMAIL_SIZE);
}

void* row_slot(Table* table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    if (page == nullptr) {
        page = table->pages[page_num] = new char[PAGE_SIZE];
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}

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

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement)
{
    statement->type = STATEMENT_INSERT;
    char* keyword = strtok(&input_buffer->buffer[0], " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");
    if (id_string == NULL || username == NULL || email == NULL) {
        return PREPARE_SYNTAX_ERROR;
    }
    int id = atoi(id_string);
    if (strlen(username) > COLUMN_USERNAME_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(email) > COLUMN_EMAIL_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }
    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);
    return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer.c_str(), "insert", 6) == 0) {
        return prepare_insert(input_buffer, statement);
    }
    if (strncmp(input_buffer->buffer.c_str(), "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement* statement, Table* table)
{
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }
    Row* row_to_insert = &(statement->row_to_insert);
    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++) {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
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

Table* new_table()
{
    Table* table = new Table;
    table->num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = nullptr;
    }
    return table;
}

void free_table(Table* table)
{
    for (int i = 0; table->pages[i]; i++) {
        delete [] (char*)table->pages[i];
    }
    delete table;
}

int main(int argc, char** argv)
{
    Table* table = new_table();

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
}
