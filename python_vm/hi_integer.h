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
};

#endif  // HI_INTEGER_H_
