#include "frame_object.h"
#include "code_object.h"
#include "hi_object.h"
#include "function_object.h"

using namespace std;

FrameObject::FrameObject(CodeObject* codes)
	: _stack(new ArrayList<HiObject*>(codes->_stack_size))
	, _loop_stack(new ArrayList<Block*>())
	, _consts(codes->_consts)
	, _names(codes->_names)
	, _locals(new Map<HiObject*, HiObject*>())
	, _globals(_locals)
	, _fast_locals(nullptr)
	, _codes(codes)
	, _pc(0)
	, _parent(nullptr)
{

}

FrameObject::FrameObject(FunctionObject* func, ObjList args)
	: FrameObject(func->_func_code)
{
	_globals = func->globals();

	if (args) {
		_fast_locals = new ArrayList<HiObject*>();
		for (int i = 0; i < args->length(); i++) {
			_fast_locals->set(i, args->get(i));
		}
	}
}

FrameObject::~FrameObject()
{
	delete _locals;
	delete _stack;
	delete _loop_stack;
}

int FrameObject::get_op_arg() const
{
	int byte1 = _codes->_bytecodes->value()[_pc++] & 0xFF;
	int byte2 = _codes->_bytecodes->value()[_pc++] & 0xFF;
	return byte2 << 8 | byte1;
}

unsigned char FrameObject::get_op_code() const
{
	return _codes->_bytecodes->value()[_pc++];
}

bool FrameObject::has_more_codes() const
{
	return _pc < _codes->_bytecodes->length();
}
