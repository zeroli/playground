#pragma once

#ifndef HI_OBJECT_H_
#define HI_OBJECT_H_

class HiObject {
public:
	virtual ~HiObject() = default;

	virtual void print() const { }
	virtual HiObject* add(HiObject* x) {
		return nullptr;
	}
};

#endif  // HI_OBJECT_H_