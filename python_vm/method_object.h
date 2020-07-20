#pragma once
#ifndef METHOD_OBJECT_H_
#define METHOD_OBJECT_H_

#include "klass.h"
#include "function_object.h"
#include "hi_object.h"

class MethodKlass : public Klass
{
private:
	MethodKlass();
	static MethodKlass* instance;

public:
	static MethodKlass* get_instance();
};

class MethodObject : public HiObject
{
	friend class MethodKlass;
private:
	HiObject* _owner;
	FunctionObject* _func;

public:
	MethodObject(FunctionObject* func);
	MethodObject(FunctionObject* func, HiObject* owner);

	void set_owner(HiObject* x) { _owner = x; }
	HiObject* owner() const { return _owner; }
	FunctionObject* func() const { return _func; }

	static bool is_function(HiObject* x);
};

#endif  // METHOD_OBJECT_H_