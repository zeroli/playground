#pragma once
#ifndef MAP_H_
#define MAP_H_

template <typename K, typename V>
class MapEntry {
public:
	K _k;
	V _v;

	MapEntry(const MapEntry<K, V>& entry) {
		_k = entry._k;
		_v = entry._v;
	}
	MapEntry(K k, V v) : _k(k), _v(v) { }
	MapEntry() : _k(0), _v(0) { }
};

template <typename K, typename V>
class Map {
private:
	MapEntry<K, V>* _entries;
	int _size;
	int _length;

	void expand() {
		if (_size >= _length) {
			MapEntry<K, V>* new_entries = new MapEntry<K, V>[_length << 1];
			for (int i = 0; i < _size; i++) {
				new_entries[i] = _entries[i];
			}
			_length <<= 1;
			delete[] _entries;
			_entries = new_entries;
		}
	}

public:
	Map() {
		_entries = new MapEntry<K, V>[8];
		_length = 8;
		_size = 0;
	}
	~Map() {
		delete[] _entries;
	}

	int size() const { return _size; }
	void put(K k, V v) {
		for (int i = 0; i < _size; i++) {
			if (_entries[i]._k->equal(k) == Universe::HiTrue) {
				_entries[i]._v = v;
				return;
			}
		}

		expand();
		_entries[_size++] = MapEntry<K, V>(k, v);
	}

	V get(K k) const {
		int i = index(k);
		if (i < 0)
			return Universe::HiNone;
		else
			return _entries[i]._v;
	}
	K get_key(int index) {
		return _entries[index]._k;
	}

	bool has_key(K k) const {
		int i = index(k);
		return i >= 0;
	}
	V remove(K k) {
		int i = index(k);
		if (i < 0)
			return 0;
		V v = _entries[i]._v;
		_entries[i] = _entries[--_size];
		return v;
	}
	int index(K k) const {
		for (int i = 0; i < _size; i++) {
			if (_entries[i]._k->equal(k) == Universe::HiTrue) {
				return i;
			}
		}
		return -1;
	}

	MapEntry<K, V>* entries() const { return _entries; }
};
#endif  // MAP_H_
