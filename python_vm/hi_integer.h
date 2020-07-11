#pragma once
#ifndef HI_INTEGER_H_
#define HI_INTEGER_H_

#include "hi_object.h"
#include "klass.h"

class IntegerKlass : public Klass {
private:
	IntegerKlass();
	static IntegerKlass* instance;

public:
	static IntegerKlass* get_instance();

	virtual void print(const HiObject* obj) const;

	virtual HiObject* greater(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* less(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* equal(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* not_equal(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* ge(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* le(const HiObject* x, const HiObject* y) const override;

	virtual HiObject* add(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* sub(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* mul(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* div(const HiObject* x, const HiObject* y) const override;
	virtual HiObject* mod(const HiObject* x, const HiObject* y) const override;
};

class HiInteger : public HiObject {
private:
	int _value;
public:
	explicit HiInteger(int x);

	int value() const { return _value; }
};

#endif  // HI_INTEGER_H_
