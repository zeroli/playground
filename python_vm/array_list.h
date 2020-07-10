#pragma once

#include <cstdio>

template <typename Ty>
class ArrayList {
private:
	int _length;
	Ty* _array;
	int _size;

	void expand();

public:
	ArrayList(int n = 8);
	
	void add(Ty t);
	void insert(int index, Ty t);
	Ty get(int index) const;
	void set(int index, Ty t);
	int size() const;
	int length() const;
	Ty pop();
};

template <typename Ty>
ArrayList<Ty>::ArrayList(int n) {
	_length = n;
	_size = 0;
	_array = new Ty[n];
}

template <typename Ty>
void ArrayList<Ty>::add(Ty t) {
	if (_size >= _length) {
		expand();
	}
	_array[_size++] = t;
}

template <typename Ty>
void ArrayList<Ty>::insert(int index, Ty t) {
	add(NULL);

	for (int i = _size; i > index; i--) {
		_array[i] = _array[i - 1];
	}
	_array[index] = t;
}

template <typename Ty>
void ArrayList<Ty>::expand() {
	Ty* new_array = new Ty[_length << 1];
	for (int i = 0; i < _length; i++) {
		new_array[i] = _array[i];
	}
	delete[] _array;
	_array = new_array;
	_length <<= 1;
	fprintf(stderr, "expand an array to %d, size is %d\n", _length, _size);
}

template <typename Ty>
int ArrayList<Ty>::size() const {
	return _size;
}

template <typename Ty>
int ArrayList<Ty>::length() const {
	return _length;
}

template <typename Ty>
Ty ArrayList<Ty>::get(int index) const {
	return _array[index];
}

template <typename Ty>
void ArrayList<Ty>::set(int index, Ty t) {
	if (_size <= index) {
		_size = index + 1;
	}
	while (_size > _length) {
		expand();
	}
	_array[index] = t;
}

template <typename Ty>
Ty ArrayList<Ty>::pop() {
	return _array[--_size];
}
