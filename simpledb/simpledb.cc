#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

int main(int argc, char** argv)
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer.c_str(), ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(0);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer.c_str());
        }
    }
}
