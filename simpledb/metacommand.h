#ifndef SIMPLEDB_METACOMMAND_H_
#define SIMPLEDB_METACOMMAND_H_

enum MetaCommandResult {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
};

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
    if (input_buffer->buffer == ".exit") {
        db_close(table);
        exit(0);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

#endif  // SIMPLEDB_METACOMMAND_H_
