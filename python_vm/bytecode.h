#pragma once

#ifndef BYTE_CODE_H_
#define BYTE_CODE_H_

class ByteCode {
public:
	static const unsigned char BINARY_ADD = 23;
	static const unsigned char PRINT_ITEM = 71;
	static const unsigned char PRINT_NEWLINE = 72;
	static const unsigned char RETURN_VALUE = 83;

	static const unsigned char HAVE_ARGUMENT = 90;
	// index in const list
	static const unsigned char LOAD_CONST = 100;
};

#endif  // BYTE_CODE_H_
