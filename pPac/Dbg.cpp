#include "Dbg.h"

Dbg*	instance = NULL;

Dbg::Dbg()
{
}


Dbg::~Dbg()
{
}

Dbg* Dbg::getDbg()
{
	if (instance == NULL)
		instance = new Dbg();

	return instance;
}

void Dbg::print(const char* arg, ...)
{
	char buf[2048];
	va_list ptr;
	va_start(ptr, arg);
	vsprintf(buf, arg, ptr);
	OutputDebugString(buf);
}
