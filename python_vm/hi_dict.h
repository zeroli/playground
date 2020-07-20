#pragma once
#ifndef HI_DICT_H_
#define HI_DICT_H_

#include "hi_object.h"
#include "klass.h"
#include "map.h"

class DictKlass : public Klass {
private:
	DictKlass();
	static DictKlass* instance;

public:
	static DictKlass* get_instance();

	virtual HiObject* subscr(HiObject* x, HiObject* y);
	virtual HiObject* iter(HiObject* x);
	virtual void print(const HiObject* x) const override;
	virtual void store_subscr(const HiObject* x, const HiObject* y, const HiObject* z);
};

class HiDict : public HiObject {
	friend class DictKlass;
private:
	Map<HiObject*, HiObject*>* _map;

public:
	HiDict();
	HiDict(Map<HiObject*, HiObject*>* map);
	Map<HiObject*, HiObject*>* map() const { return _map; }

	void put(HiObject* k, HiObject* v) { _map->put(k, v); }
	HiObject* get(HiObject* k) const { return _map->get(k); }
	bool has_key(HiObject* k) const { return _map->has_key(k); }
	int size() const { return _map->size(); }
	HiObject* remove(HiObject* k) { return _map->remove(k); }

};

#endif  // HI_DICT_H_
