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

struct Pager {
    FILE* fp;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
};

struct Table {
    Pager* pager;
    uint32_t num_rows;
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

void * get_page(Pager* pager, uint32_t page_num)
{
    if (page_num > TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bound. %d > %d\n",
            page_num, TABLE_MAX_PAGES);
        exit(-1);
    }
    if (pager->pages[page_num] == NULL) {
        // cache miss, allocate memory and load from file
        void* page = new char[PAGE_SIZE];
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        // we might save a partial page at the end of the file
        if (pager->file_length % PAGE_SIZE) {
            num_pages += 1;
        }

        if (page_num <= num_pages) {
            fseek(pager->fp, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = fread(page, PAGE_SIZE, 1, pager->fp);
            if (bytes_read == -1) {
                printf("Error reading file: %d\n", ferror(pager->fp));
                exit(-1);
            }
        }
        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}

void* row_slot(Table* table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = get_page(table->pager, page_num);

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return (char*)page + byte_offset;
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

void db_close(Table* table);

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
    if (input_buffer->buffer == ".exit") {
        db_close(table);
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

void pager_flush(Pager* pager, uint32_t page_num, uint32_t size)
{
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(1);
    }
    off_t offset = fseek(pager->fp, page_num * PAGE_SIZE, SEEK_SET);
    if (offset == -1) {
        printf("Error seeking: %d\n", ferror(pager->fp));
        exit(-1);
    }
    ssize_t bytes_written = fwrite(pager->pages[page_num], size, 1, pager->fp);
    if (bytes_written == -1) {
        printf("Error writing: %d\n", ferror(pager->fp));
        exit(-1);
    }
}

Pager* pager_open(const char* filename)
{
    FILE* fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("unable to open file %s\n", filename);
        exit(-1);
    }
    off_t file_length = fseek(fp, 0, SEEK_END);
    Pager* pager = new Pager();
    pager->fp = fp;
    pager->file_length = file_length;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }
    return pager;
}

Table* db_open(const char* filename)
{
    Pager* pager = pager_open(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;

    Table* table = new Table;
    table->pager = pager;
    table->num_rows = num_rows;

    return table;
}

void db_close(Table* table)
{
    Pager* pager = table->pager;
    uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;

    for (uint32_t i = 0; i < num_full_pages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }
        pager_flush(pager, i, PAGE_SIZE);
        delete [] (char*)pager->pages[i];
        pager->pages[i] = NULL;
    }

    // there might be a partial page to write to the end of the file
    // this should not be needed after we switch to a B-tree
    uint32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;
    if (num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if (pager->pages[page_num] != NULL) {
            pager_flush(pager, page_num, num_additional_rows * ROW_SIZE);
            delete [] (char*)pager->pages[page_num];
            pager->pages[page_num] = NULL;
        }
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
