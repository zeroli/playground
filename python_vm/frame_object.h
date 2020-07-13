#pragma once
#ifndef FRAME_OBJECT_H_
#define FRAME_OBJECT_H_

#include "array_list.h"
#include "map.h"

class HiObject;
class CodeObject;
class Block;
class FunctionObject;

typedef ArrayList<HiObject*>* ObjList;

class FrameObject {
public:
	explicit FrameObject(CodeObject* codes);
	explicit FrameObject(FunctionObject* func, ObjList args);
	~FrameObject();

	ArrayList<HiObject*>* _stack;
	ArrayList<Block*>* _loop_stack;

	ArrayList<HiObject*>* _consts;
	ArrayList<HiObject*>* _names;

	Map<HiObject*, HiObject*>* _locals;
	Map<HiObject*, HiObject*>* _globals;
	ArrayList<HiObject*>* _fast_locals;

	CodeObject* _codes;
	mutable int _pc;

	FrameObject* _parent;
public:
	void set_pc(int x) { _pc = x; }
	int get_pc() const { return _pc; }

	void set_parent(FrameObject* x) { _parent = x; }
	FrameObject* get_parent() const { return _parent; }
	bool is_first_frame() const { return _parent == nullptr; }

	ArrayList<HiObject*>* stack() const { return _stack; }
	ArrayList<Block*>* loop_stack() const { return _loop_stack; }
	ArrayList<HiObject*>* consts() const { return _consts; }
	ArrayList<HiObject*>* names() const { return _names; }
	Map<HiObject*, HiObject*>* locals() const { return _locals; }
	Map<HiObject*, HiObject*>* globals() const { return _globals; }
	ArrayList<HiObject*>* fast_locals() const { return _fast_locals;  }

	bool has_more_codes() const;
	unsigned char get_op_code() const;
	int get_op_arg() const;
};
#endif  // FRAME_OBJECT_H_