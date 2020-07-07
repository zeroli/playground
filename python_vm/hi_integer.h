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

	virtual void print() const override {
		printf("%d", _value);
	}

	virtual HiObject* add(HiObject* x) {
		return new HiInteger(_value + ((HiInteger*)x)->_value);
	}
};

#endif  // HI_INTEGER_H_
