#ifndef SIMPLEDB_INPUTBUFFER_H_
#define SIMPLEDB_INPUTBUFFER_H_

#include <string>

struct InputBuffer {
    std::string buffer;
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

void read_input(InputBuffer* input_buffer)
{
    std::getline(std::cin, input_buffer->buffer);
    if (input_buffer->buffer.empty()) {
        printf("Error reading input\n");
        exit(-1);
    }
}

#endif  // SIMPLEDB_INPUTBUFFER_H_
