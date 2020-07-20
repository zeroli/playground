#include "hi_string.h"
#include "universe.h"
#include "hi_integer.h"

#include <cstring>
#include <cassert>
#include <cstdio>
#include <algorithm>

StringKlass* StringKlass::instance = nullptr;

StringKlass::StringKlass() {

}

StringKlass* StringKlass::get_instance() {
	if (instance == nullptr)
		instance = new StringKlass();
	return instance;
}

void StringKlass::print(const HiObject* obj) const
{
	if (obj->klass() != this)
		return;
	const HiString* x = static_cast<const HiString*>(obj);
	for (int i = 0; i < x->length(); i++) {
		printf("%c", x->value()[i]);
	}
	fflush(stdout);
}

template <typename Op>
HiObject* compareString(const HiObject* x, const HiObject* y, Op op)
{
	if (x->klass() != y->klass())
		return Universe::HiFalse;

	const HiString* ix = static_cast<const HiString*>(x);
	const HiString* iy = static_cast<const HiString*>(y);
	assert(ix && (ix->klass() == (Klass*)StringKlass::get_instance()));
	assert(iy && (iy->klass() == (Klass*)StringKlass::get_instance()));

	return op((void*)ix->value(), (void*)iy->value(), std::min(ix->length(), iy->length())) ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* StringKlass::greater(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) > 0; });
}

HiObject* StringKlass::less(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) < 0; });
}

HiObject* StringKlass::equal(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) == 0; });
}

HiObject* StringKlass::not_equal(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) != 0; });
}

HiObject* StringKlass::ge(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) >= 0; });
}

HiObject* StringKlass::le(const HiObject* x, const HiObject* y) const
{
	return compareString(x, y, [](void* xp, void* yp, int len) { return memcmp(xp, yp, len) <= 0; });
}

HiObject* StringKlass::add(const HiObject* x, const HiObject* y) const
{
	if (x->klass() != y->klass())
		return nullptr;

	const HiString* ix = static_cast<const HiString*>(x);
	const HiString* iy = static_cast<const HiString*>(y);
	assert(ix && (ix->klass() == (Klass*)StringKlass::get_instance()));
	assert(iy && (iy->klass() == (Klass*)StringKlass::get_instance()));

	int new_len = ix->length() + iy->length();
	char* new_value = new char[new_len];
	memcpy(new_value, ix->value(), ix->length());
	memcpy(new_value + ix->length(), iy->value(), iy->length());
	// TODO: reduce one memory copy
	HiString* ret = new HiString(new_value, new_len);
	delete[] new_value;
	return ret;
}

HiObject* StringKlass::sub(const HiObject* x, const HiObject* y) const
{
	// no implementation for it
	return nullptr;
}

HiObject* StringKlass::mul(const HiObject* x, const HiObject* y) const
{
	// no implementation for it
	return nullptr;
}

HiObject* StringKlass::div(const HiObject* x, const HiObject* y) const
{
	// no implementation for it
	return nullptr;
}

HiObject* StringKlass::mod(const HiObject* x, const HiObject* y) const
{
	// no implementation for it
	return nullptr;
}

HiObject* StringKlass::len(const HiObject* x) const
{
	return new HiInteger(((const HiString*)x)->length());
}

HiString::HiString(const char* x)
	: HiString(x, strlen(x))
{
}

HiString::HiString(const char* x, int length) {
	_length = length;
	_value = new char[_length];
	memcpy(_value, x, _length);
	set_klass(StringKlass::get_instance());
}
