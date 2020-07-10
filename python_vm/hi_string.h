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

	virtual HiObject* add(HiObject* x) const override;

	virtual HiObject* greater(HiObject* x) const override;
	virtual HiObject* less(HiObject* x) const override;
	virtual HiObject* equal(HiObject* x) const override;
	virtual HiObject* not_equal(HiObject* x) const override;
	virtual HiObject* ge(HiObject* x) const override;
	virtual HiObject* le(HiObject* x) const override;
};

#endif  // HI_STRING_H_
