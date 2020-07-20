#pragma once

#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

#include <cassert>

class Klass;

class HiObject {
private:
	Klass* _klass;
public:
	Klass* klass() const { assert(_klass != nullptr); return _klass; }
	void set_klass(Klass* x) { _klass = x; }

	virtual ~HiObject() = default;

	void print() const;
	HiObject* add(HiObject* x) const;
	HiObject* sub(HiObject* x) const;
	HiObject* mul(HiObject* x) const;
	HiObject* div(HiObject* x) const;
	HiObject* mod(HiObject* x) const;

	HiObject* greater(HiObject* x) const;
	HiObject* less(HiObject* x) const;
	HiObject* equal(HiObject* x) const;
	HiObject* not_equal(HiObject* x) const;
	HiObject* ge(HiObject* x) const;
	HiObject* le(HiObject* x) const;

	HiObject* len() const;

	HiObject* getattr(HiObject* x);
};

#endif  // HI_OBJECT_H_