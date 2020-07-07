#include "hi_string.h"

#include <cstring>

HiString::HiString(const char* x) {
	_length = strlen(x);
	_value = new char[_length];
	strncpy_s(_value, _length, x, _length);
}

HiString::HiString(const char* x, int length) {
	_length = length;
	_value = new char[_length];
	memcpy(_value, x, _length);
}
