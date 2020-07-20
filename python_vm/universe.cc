#include "universe.h"

#include "hi_integer.h"
#include "hi_string.h"
#include "hi_dict.h"
#include "function_object.h"

HiInteger* Universe::HiTrue = nullptr;
HiInteger* Universe::HiFalse = nullptr;

HiObject* Universe::HiNone = nullptr;

void Universe::genesis()
{
	HiTrue = new HiInteger(1);
	HiFalse = new HiInteger(0);

	HiNone = new HiObject();

	HiDict* klass_dict = new HiDict();
	StringKlass::get_instance()->set_klass_dict(klass_dict);
	klass_dict->put(new HiString("upper"), new FunctionObject(string_upper));
}

void Universe::destroy()
{
	delete HiTrue;
	HiTrue = nullptr;
	delete HiFalse;
	HiFalse = nullptr;
	delete HiNone;
	HiNone = nullptr;
}