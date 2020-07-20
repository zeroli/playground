#include "hi_object.h"

#include "klass.h"

void HiObject::print() const
{
	klass()->print(this);
}

HiObject* HiObject::add(HiObject* x) const
{
	return klass()->add(this, x);
}

HiObject* HiObject::sub(HiObject* x) const
{
	return klass()->sub(this, x);
}

HiObject* HiObject::mul(HiObject* x) const
{
	return klass()->mul(this, x);
}

HiObject* HiObject::div(HiObject* x) const
{
	return klass()->div(this, x);
}

HiObject* HiObject::mod(HiObject* x) const
{
	return klass()->mod(this, x);
}

HiObject* HiObject::greater(HiObject* x) const
{
	return klass()->greater(this, x);
}

HiObject* HiObject::less(HiObject* x) const
{
	return klass()->less(this, x);
}

HiObject* HiObject::equal(HiObject* x) const
{
	return klass()->equal(this, x);
}

HiObject* HiObject::not_equal(HiObject* x) const
{
	return klass()->not_equal(this, x); 
}

HiObject* HiObject::ge(HiObject* x) const
{
	return klass()->ge(this, x);
}

HiObject* HiObject::le(HiObject* x) const
{
	return klass()->le(this, x);
}

HiObject* HiObject::len() const
{
	return klass()->len(this);
}