#pragma once
#ifndef HI_INTEGER_H_
#define HI_INTEGER_H_

#include "hi_object.h"

class HiInteger : public HiObject {
private:
	int _value;
public:
	explicit HiInteger(int x) : _value(x) { }

	int value() const { return _value; }

	virtual void print() const override;

	virtual HiObject* add(HiObject* x) const override;

	virtual HiObject* greater(HiObject* x) const override;
	virtual HiObject* less(HiObject* x) const override;
	virtual HiObject* equal(HiObject* x) const override;
	virtual HiObject* not_equal(HiObject* x) const override;
	virtual HiObject* ge(HiObject* x) const override;
	virtual HiObject* le(HiObject* x) const override;
};

#endif  // HI_INTEGER_H_
