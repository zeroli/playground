#pragma once
#ifndef KLASS_H_
#define KLASS_H_

class HiString;
class HiObject;
class HiDict;

class Klass {
private:
	HiString* _name;
	HiDict* _klass_dict;
public:
	Klass() { }

	void set_name(HiString* x) { _name = x; }
	HiString* name() const { return _name; }
	void set_klass_dict(HiDict* dict) { _klass_dict = dict; }
	HiDict* klass_dict() const { return _klass_dict; }

	virtual void print(const HiObject* obj) const { }

	virtual HiObject* greater(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* less(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* equal(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* not_equal(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* ge(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* le(const HiObject* x, const HiObject* y) const { return nullptr; }

	virtual HiObject* add(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* sub(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* mul(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* div(const HiObject* x, const HiObject* y) const { return nullptr; }
	virtual HiObject* mod(const HiObject* x, const HiObject* y) const { return nullptr; }

	virtual HiObject* len(const HiObject* x) const { return nullptr; }
};

#endif  // KLASS_H_