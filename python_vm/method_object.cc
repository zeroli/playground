#include "method_object.h"

#include "hi_dict.h"

MethodKlass* MethodKlass::instance = nullptr;
MethodKlass::MethodKlass()
{
	set_klass_dict(new HiDict);
}

MethodKlass* MethodKlass::get_instance()
{
	if (instance == nullptr)
		instance = new MethodKlass();
	return instance;
}

MethodObject::MethodObject(FunctionObject* func)
	: _owner(nullptr), _func(func)
{
	set_klass(MethodKlass::get_instance());
}

MethodObject::MethodObject(FunctionObject* func, HiObject* owner)
	: _owner(owner), _func(func)
{
	set_klass(MethodKlass::get_instance());
}

bool MethodObject::is_function(HiObject* x)
{
	return dynamic_cast<FunctionObject*>(x) != nullptr;
}