#include "function_object.h"
#include "code_object.h"

#include <cstdio>
#include <cassert>

FunctionKlass* FunctionKlass::instance = nullptr;

FunctionKlass* FunctionKlass::get_instance()
{
	if (instance == nullptr)
		instance = new FunctionKlass();

	return instance;
}

void FunctionKlass::print(const HiObject* obj) const
{
	printf("<function: ");
	const FunctionObject* fo = static_cast<const FunctionObject*>(obj);
	assert(fo && fo->klass() == (Klass*)this);
	fo->func_name()->print();
	printf(">");
}

NativeFunctionKlass* NativeFunctionKlass::instance = nullptr;

NativeFunctionKlass* NativeFunctionKlass::get_instance()
{
	if (instance == nullptr)
		instance = new NativeFunctionKlass();

	return instance;
}

FunctionObject::FunctionObject(HiObject* code_object)
{
	CodeObject* co = (CodeObject*)code_object;

	_func_code = co;
	_func_name = co->_co_name;
	_flags = co->_flag;
	_globals = nullptr;
	_defaults = nullptr;

	set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPointer nfp)
{
	_func_code = nullptr;
	_func_name = nullptr;
	_flags = 0;
	_globals = nullptr;
	_native_func = nfp;

	set_klass(NativeFunctionKlass::get_instance());
}

HiObject* FunctionObject::call(ObjList args)
{
	assert(_native_func);
	return (*_native_func)(args);
}

void FunctionObject::set_defaults(ArrayList<HiObject *>* defaults)
{
	if (defaults == nullptr) {
		delete defaults;
		return;
	}
	_defaults = new ArrayList<HiObject*>(defaults->length());
	for (int i = 0; i < defaults->length(); i++) {
		_defaults->set(i, defaults->get(i));
	}
}

HiObject* len(ObjList args)
{
	return args->get(0)->len();
}

HiObject* string_upper(ObjList args)
{
	HiObject* arg0 = args->get(0);
	assert(arg0->klass() == StringKlass::get_instance());

	HiString* str_obj = (HiString*)arg0;

	int length = str_obj->length();
	if (length < 0)
		return Universe::HiNone;

	char* v = new char[length];
	char c;
	for (int i = 0; i < length; i++) {
		c = str_obj->value()[i];
		if (c >= 'a' && c <= 'z')
			v[i] = c - 0x20;
		else
			v[i] = c;
	}

	HiString* s = new HiString(v, length);
	delete[] v;

	return s;
}