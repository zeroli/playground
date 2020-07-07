#pragma once
#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "array_list.h"

class CodeObject;
class HiObject;
class HiString;

class Interpreter {
public:
	Interpreter()
		: _bytecodes(nullptr), _stack(nullptr), _consts(nullptr)
	{}

	void run(CodeObject* codes);

private:
	HiString* _bytecodes;
	ArrayList<HiObject*>* _stack;
	ArrayList<HiObject*>* _consts;
};

#endif  // INTERPRETER_H_
