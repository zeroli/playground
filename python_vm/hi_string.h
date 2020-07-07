#pragma once

#ifndef HI_STRING_H_
#define HI_STRING_H_

#include "hi_object.h"

class HiString : public HiObject {
private:
	char* _value;
	int _length;
public:
	HiString(const char* x);
	HiString(const char* x, int length);

	const char* value() const { return _value; }
	int length() const { return _length; }
};

#endif  // HI_STRING_H_
