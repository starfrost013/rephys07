#pragma once
#include <util/Debug.h>

using namespace RBX;

void Debugable::doCrash()
{
	if (doCrashEnabled)
	{
		char* zero = nullptr;
		char* four = (char*)0x00000003;

		// Guaranteed crash.
		// Yes, this is how they programmed it.
#pragma warning (disable : 6011)
		*zero = *four;
#pragma warning (pop)
	}

}