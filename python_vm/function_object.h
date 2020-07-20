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

class NativeFunctionKlass : public Klass {
private:
	NativeFunctionKlass() = default;
	static NativeFunctionKlass* instance;

public:
	static NativeFunctionKlass* get_instance();
};

HiObject* len(ObjList args);
typedef HiObject* (*NativeFuncPointer)(ObjList args);

HiObject* string_upper(ObjList args);

class FunctionObject : public HiObject {
	friend class FunctionKlass;
	friend class FrameObject;

private:
	CodeObject* _func_code;
	HiString* _func_name;
	Map<HiObject*, HiObject*>* _globals;
	ObjList _defaults;

	unsigned int _flags;

	NativeFuncPointer _native_func;
public:
	explicit FunctionObject(HiObject* code_object);
	explicit FunctionObject(Klass* klass)
		: _func_code(nullptr), _func_name(nullptr), _globals(nullptr), _defaults(nullptr), _flags(0)
	{
		set_klass(klass);
	}
	explicit FunctionObject(NativeFuncPointer nfp);

	CodeObject* func_code() const { return _func_code; }
	HiString* func_name() const { return _func_name; }
	Map<HiObject*, HiObject*>* globals() const { return _globals;  }
	int flags() const { return _flags; }

	void set_globals(Map<HiObject*, HiObject*>* globals) { _globals = globals; }
	void set_defaults(ArrayList<HiObject*>* defaults);

	HiObject* call(ObjList args);
};


#endif  // FUNCTION_OBJECT_H_
