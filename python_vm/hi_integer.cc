#include "hi_integer.h"

#include <cstdio>

#include "universe.h"

IntegerKlass* IntegerKlass::instance = nullptr;

IntegerKlass::IntegerKlass() {

}

IntegerKlass* IntegerKlass::get_instance() {
	if (instance == nullptr)
		instance = new IntegerKlass();
	return instance;
}

void IntegerKlass::print(const HiObject* obj) const
{
	if (obj->klass() != this)
		return;
	const HiInteger* x = static_cast<const HiInteger*>(obj);
	printf("%d", x->value());
	fflush(stdout);
}

template <typename Op>
HiObject* compareInteger(const HiObject* x, const HiObject* y, Op op)
{
	if (x->klass() != y->klass())
		return Universe::HiFalse;

	const HiInteger* ix = static_cast<const HiInteger*>(x);
	const HiInteger* iy = static_cast<const HiInteger*>(y);
	assert(ix && (ix->klass() == (Klass*)IntegerKlass::get_instance()));
	assert(iy && (iy->klass() == (Klass*)IntegerKlass::get_instance()));

	return op(ix->value(), iy->value()) ? Universe::HiTrue : Universe::HiFalse;
}

HiObject* IntegerKlass::greater(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv > yv; });
}

HiObject* IntegerKlass::less(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv < yv; });
}

HiObject* IntegerKlass::equal(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv == yv; });
}

HiObject* IntegerKlass::not_equal(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv != yv; });
}

HiObject* IntegerKlass::ge(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv >= yv; });
}

HiObject* IntegerKlass::le(const HiObject* x, const HiObject* y) const
{
	return compareInteger(x, y, [](int xv, int yv) { return xv <= yv; });
}

template <typename Op>
HiObject* arithmetricInteger(const HiObject* x, const HiObject* y, Op op)
{
	if (x->klass() != y->klass())
		return nullptr;

	const HiInteger* ix = static_cast<const HiInteger*>(x);
	const HiInteger* iy = static_cast<const HiInteger*>(y);
	assert(ix && (ix->klass() == (Klass*)IntegerKlass::get_instance()));
	assert(iy && (iy->klass() == (Klass*)IntegerKlass::get_instance()));

	return new HiInteger(op(ix->value(), iy->value()));
}

HiObject* IntegerKlass::add(const HiObject* x, const HiObject* y) const
{
	return arithmetricInteger(x, y, [](int xv, int yv) { return xv + yv; });
}

HiObject* IntegerKlass::sub(const HiObject* x, const HiObject* y) const
{
	return arithmetricInteger(x, y, [](int xv, int yv) { return xv - yv; });
}

HiObject* IntegerKlass::mul(const HiObject* x, const HiObject* y) const
{
	return arithmetricInteger(x, y, [](int xv, int yv) { return xv * yv; });
}

HiObject* IntegerKlass::div(const HiObject* x, const HiObject* y) const
{
	return arithmetricInteger(x, y, [](int xv, int yv) { return xv / yv; });
}

HiObject* IntegerKlass::mod(const HiObject* x, const HiObject* y) const
{
	return arithmetricInteger(x, y, [](int xv, int yv) { return xv % yv; });
}

HiInteger::HiInteger(int x)
	: _value(x)
{
	set_klass(IntegerKlass::get_instance());
}
