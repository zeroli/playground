#pragma once
#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "array_list.h"
#include "map.h"

class CodeObject;
class HiObject;
class HiString;
class FrameObject;

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
		: _frame(nullptr), _vars(nullptr)
	{}
	~Interpreter();

	void run(CodeObject* codes);

private:
	void eval_frame();
	void leave_frame();
	void destroy_frame();
	void build_frame(HiObject* callable);
private:
	FrameObject* _frame;  // current frame which is running
	Map<HiObject*, HiObject*>* _vars;
	HiObject* _ret_value;
};

#endif  // INTERPRETER_H_
