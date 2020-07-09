#include <cstdlib>

#include "buffered_input_stream.h"
#include "binaryfile_parser.h"
#include "interpreter.h"
#include "universe.h"

int main(int argc, char** argv)
{
	if (argc <= 1) {
		printf("vm need a parameter: filename\n");
		exit(-1);
	}
	Universe::genesis();
	BufferedInputStream stream(argv[1]);
	BinaryFileParser parser(&stream);
	CodeObject* main_code = parser.parse();

	Interpreter interpreter;
	interpreter.run(main_code);

	Universe::destroy();
	return 0;
}