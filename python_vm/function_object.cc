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