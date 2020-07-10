#include "hi_string.h"
#include "hi_integer.h"
#include "universe.h"

#include <cstring>
#include <cassert>

HiString::HiString(const char* x) {
	_length = strlen(x);
	_value = new char[_length];
	strncpy_s(_value, _length, x, _length);
}

HiString::HiString(const char* x, int length) {
	_length = length;
	_value = new char[_length];
	memcpy(_value, x, _length);
}

HiObject* HiString::add(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	int new_len = _length + x1->_length;
	char* new_value = new char[new_len];
	memcpy(new_value, _value, _length);
	memcpy(new_value + _length, x1->_value, x1->_length);
	HiString* ret = new HiString(new_value, new_len);
	delete[] new_value;
	return ret;
}

HiObject* HiString::greater(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) > 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiString::less(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) < 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiString::equal(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) == 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiString::not_equal(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) != 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiString::ge(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) >= 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiString::le(HiObject* x) const
{
	HiString* x1 = static_cast<HiString*>(x);
	assert(x1);
	if (strncmp(_value, x1->_value, _length) <= 0)
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}