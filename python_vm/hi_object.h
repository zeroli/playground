#pragma once

#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

class HiObject {
public:
	virtual ~HiObject() = default;

	virtual void print() const { }
	virtual HiObject* add(HiObject* x) const {
		return nullptr;
	}

	virtual HiObject* greater(HiObject* x) const { return nullptr; }
	virtual HiObject* less(HiObject* x) const { return nullptr; }
	virtual HiObject* equal(HiObject* x) const { return nullptr; }
	virtual HiObject* not_equal(HiObject* x) const { return nullptr; }
	virtual HiObject* ge(HiObject* x) const { return nullptr; }
	virtual HiObject* le(HiObject* x) const { return nullptr; }
};

#endif  // HI_OBJECT_H_