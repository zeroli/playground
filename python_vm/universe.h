#pragma once
#ifndef UNIVERSE_H_
#define UNIVERSE_H_

class HiInteger;
class HiObject;

class Universe
{
public:
	static void genesis();
	static void destroy();

	static HiInteger* HiTrue;
	static HiInteger* HiFalse;

	static HiObject* HiNone;
};

#endif  // UNIVERSE_H_