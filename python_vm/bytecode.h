#pragma once

#ifndef BYTE_CODE_H_
#define BYTE_CODE_H_

class ByteCode {
public:
	static const unsigned char POP_TOP = 1;
	static const unsigned char BINARY_ADD = 23;
	static const unsigned char PRINT_ITEM = 71;
	static const unsigned char PRINT_NEWLINE = 72;
	static const unsigned char BREAK_LOOP = 80;
	static const unsigned char RETURN_VALUE = 83;

	static const unsigned char POP_BLOCK = 87;
	static const unsigned char HAVE_ARGUMENT = 90;

	static const unsigned char STORE_NAME = 90; /* Index in name list */
	// index in const list
	static const unsigned char LOAD_CONST = 100;
	static const unsigned char LOAD_NAME = 101; /* Index in name list */
	static const unsigned char LOAD_ATTR = 106;
	// comparison operator
	static const unsigned char COMPARE_OP = 107;
	// number of bytes to skip
	static const unsigned char JUMP_FORWARD = 110;
	static const unsigned char JUMP_ABSOLUTE = 113;
	static const unsigned char POP_JUMP_IF_FALSE = 114;
	static const unsigned char LOAD_GLOBAL = 116;

	static const unsigned char SETUP_LOOP = 120; /* Target address (relative) */
	static const unsigned char LOAD_FAST = 124; /* Local variable number */
	static const unsigned char STORE_FAST = 125; /* Local variable number */

	static const unsigned char CALL_FUNCTION = 131;
	static const unsigned char MAKE_FUNCTION = 132;

	static void initialize();
	static const char* lookup(unsigned char op_code);
};

enum COMPARE {
	LESS = 0,
	LESS_EQUAL = 1,
	EQUAL = 2,
	NOT_EQUAL = 3,
	GREATER = 4,
	GREATER_EQUAL = 5,
	IS = 8,
	IS_NOT = 9,

};

#endif  // BYTE_CODE_H_
