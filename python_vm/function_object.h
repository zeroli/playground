#pragma once
#ifndef FUNCTION_OBJECT_H_
#define FUNCTION_OBJECT_H_

#include "Klass.h"
#include "hi_object.h"
#include "frame_object.h"

class FunctionKlass : public Klass
{
private:
	FunctionKlass() = default;
	static FunctionKlass* instance;

public:
	static FunctionKlass* get_instance();

	virtual void print(const HiObject* obj) const override;
};

class FunctionObject : public HiObject {
	friend class FunctionKlass;
	friend class FrameObject;

private:
	CodeObject* _func_code;
	HiString* _func_name;
	Map<HiObject*, HiObject*>* _globals;

	unsigned int _flags;

public:
	explicit FunctionObject(HiObject* code_object);
	explicit FunctionObject(Klass* klass)
		: _func_code(nullptr), _func_name(nullptr), _globals(nullptr), _flags(0)
	{
		set_klass(klass);
	}

	CodeObject* func_code() const { return _func_code; }
	HiString* func_name() const { return _func_name; }
	Map<HiObject*, HiObject*>* globals() const { return _globals;  }
	int flags() const { return _flags; }

	void set_globals(Map<HiObject*, HiObject*>* globals) { _globals = globals; }
};


#endif  // FUNCTION_OBJECT_H_
