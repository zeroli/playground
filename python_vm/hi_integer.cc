#include "hi_integer.h"

#include <cstdio>

#include "universe.h"

void HiInteger::print() const
{
	printf("%d", _value);
}

HiObject* HiInteger::add(HiObject* x) const
{
	return new HiInteger(_value + ((HiInteger*)x)->_value);
}

HiObject* HiInteger::greater(HiObject* x) const
{
	if (_value > (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiInteger::less(HiObject* x) const
{
	if (_value < (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiInteger::equal(HiObject* x) const
{
	if (_value == (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiInteger::not_equal(HiObject* x) const
{
	if (_value != (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiInteger::ge(HiObject* x) const
{
	if (_value >= (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}

HiObject* HiInteger::le(HiObject* x) const
{
	if (_value <= (((HiInteger*)x)->_value))
		return Universe::HiTrue;
	else
		return Universe::HiFalse;
}