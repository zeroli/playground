#include "universe.h"

#include "hi_integer.h"

HiInteger* Universe::HiTrue = nullptr;
HiInteger* Universe::HiFalse = nullptr;

HiObject* Universe::HiNone = nullptr;

void Universe::genesis()
{
	HiTrue = new HiInteger(1);
	HiFalse = new HiInteger(0);

	HiNone = new HiObject();
}

void Universe::destroy()
{
	delete HiTrue;
	HiTrue = nullptr;
	delete HiFalse;
	HiFalse = nullptr;
	delete HiNone;
	HiNone = nullptr;
}