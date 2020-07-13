#include "bytecode.h"

#include <unordered_map>

#define STR_OP_CODE(op_code) #op_code

static std::unordered_map<unsigned char, const char*> s_bytecodes;

void ByteCode::initialize()
{
	s_bytecodes[POP_TOP] = STR_OP_CODE(POP_TOP);
	s_bytecodes[BINARY_ADD] = STR_OP_CODE(BINARY_ADD);
	s_bytecodes[PRINT_ITEM] = STR_OP_CODE(PRINT_ITEM);
	s_bytecodes[PRINT_NEWLINE] = STR_OP_CODE(PRINT_NEWLINE);
	s_bytecodes[BREAK_LOOP] = STR_OP_CODE(BREAK_LOOP);
	s_bytecodes[RETURN_VALUE] = STR_OP_CODE(RETURN_VALUE);
	s_bytecodes[POP_BLOCK] = STR_OP_CODE(POP_BLOCK);
	s_bytecodes[HAVE_ARGUMENT] = STR_OP_CODE(HAVE_ARGUMENT);
	s_bytecodes[STORE_NAME] = STR_OP_CODE(STORE_NAME);
	s_bytecodes[LOAD_CONST] = STR_OP_CODE(LOAD_CONST);
	s_bytecodes[LOAD_NAME] = STR_OP_CODE(LOAD_NAME);
	s_bytecodes[COMPARE_OP] = STR_OP_CODE(COMPARE_OP);
	s_bytecodes[JUMP_FORWARD] = STR_OP_CODE(JUMP_FORWARD);
	s_bytecodes[JUMP_ABSOLUTE] = STR_OP_CODE(JUMP_ABSOLUTE);
	s_bytecodes[POP_JUMP_IF_FALSE] = STR_OP_CODE(POP_JUMP_IF_FALSE);
	s_bytecodes[SETUP_LOOP] = STR_OP_CODE(SETUP_LOOP);
	s_bytecodes[LOAD_FAST] = STR_OP_CODE(LOAD_FAST);
	s_bytecodes[STORE_FAST] = STR_OP_CODE(STORE_FAST);
	s_bytecodes[CALL_FUNCTION] = STR_OP_CODE(CALL_FUNCTION);
	s_bytecodes[MAKE_FUNCTION] = STR_OP_CODE(MAKE_FUNCTION);
}

const char* ByteCode::lookup(unsigned char op_code)
{
	auto it = s_bytecodes.find(op_code);
	if (it != s_bytecodes.end())
		return it->second;
	else
		return nullptr;
}