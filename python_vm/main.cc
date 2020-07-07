#include "buffered_input_stream.h"
#include "binaryfile_parser.h"

#include <cstdlib>

int main(int argc, char** argv)
{
	if (argc <= 1) {
		printf("vm need a parameter: filename\n");
		exit(-1);
	}
	BufferedInputStream stream(argv[1]);
	BinaryFileParser parser(&stream);
	parser.parse();

	return 0;
}