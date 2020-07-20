#include "hi_dict.h"

HiDict::HiDict()
	: _map(new Map<HiObject*, HiObject*>())
{
}

HiDict::HiDict(Map<HiObject*, HiObject*>* map)
	: _map(map)
{

}

