#pragma once
#ifndef CODE_OBJECT_H_
#define CODE_OBJECT_H_

#include "hi_object.h"
#include "array_list.h"

#include "hi_string.h"

class CodeObject : public HiObject {
public:
	CodeObject(int argcount, int nlocals, int stacksize, int flag, HiString* bytecodes,
		ArrayList<HiObject*>* consts, ArrayList<HiObject*>* names, ArrayList<HiObject*>* varnames,
		ArrayList<HiObject*>* freevars, ArrayList<HiObject*>* cellvars,
		HiString* filename, HiString* co_name, int lineno, HiString* notable) :
		_argcount(argcount),
		_nlocals(nlocals),
		_stack_size(stacksize),
		_flag(flag),
		_bytecodes(bytecodes),
		_consts(consts),
		_names(names),
		_var_names(varnames),
		_free_vars(freevars),
		_cell_vars(cellvars),
		_co_name(co_name),
		_file_name(filename),
		_lineno(lineno),
		_notable(notable)
	{}

public:
	int _argcount;
	int _nlocals;
	int _stack_size;
	int _flag;
	HiString* _bytecodes;
	ArrayList<HiObject*>* _consts;
	ArrayList<HiObject*>* _names;
	ArrayList<HiObject*>* _var_names;
	ArrayList<HiObject*>* _free_vars;
	ArrayList<HiObject*>* _cell_vars;
	HiString* _file_name;
	HiString* _co_name;
	int _lineno;
	HiString* _notable;
};
#endif  // CODE_OBJECT_H_
