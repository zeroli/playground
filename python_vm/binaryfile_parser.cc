#include "binaryfile_parser.h"

#include "code_object.h"
#include "buffered_input_stream.h"

CodeObject* get_code_object()
{
	// TODO
	return NULL;
}

CodeObject* BinaryFileParser::parse()
{
	int magic_number = file_stream->read_int();
	printf("magic number is 0x%x\n", magic_number);

	int moddate = file_stream->read_int();
	printf("moddate is 0x%x\n", moddate);

	char object_type = file_stream->read();
	if (object_type == 'c') {
		CodeObject* result = get_code_object();
		printf("parser ok!\n");
		return result;
	}
	return NULL;
}