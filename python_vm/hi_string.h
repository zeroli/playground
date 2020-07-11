#pragma once

#ifndef HI_STRING_H_
#define HI_STRING_H_

#include "hi_object.h"
#include "klass.h"

class StringKlass : public Klass
{
private:
	StringKlass();
	static StringKlass* instance;

public:
	static StringKlass* get_instance();

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
