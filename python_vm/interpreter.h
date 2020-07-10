#pragma once
#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "array_list.h"
#include "map.h"

class CodeObject;
class HiObject;
class HiString;

class Block {
public:
	unsigned char _type;
	unsigned int _target;
	int _level;

	Block(unsigned char b_type, unsigned int b_target, int b_level)
		: _type(b_type), _target(b_target), _level(b_level)
	{}
};
class Interpreter {
public:
	Interpreter()
		: _bytecodes(nullptr), _stack(nullptr), _consts(nullptr)
	{}
	~Interpreter();

	void run(CodeObject* codes);

private:
	HiString* _bytecodes;
	ArrayList<HiObject*>* _stack;
	ArrayList<HiObject*>* _consts;
	Map<HiObject*, HiObject*>* _vars;
	ArrayList<Block*>* _loop_stack;
};

#endif  // INTERPRETER_H_
