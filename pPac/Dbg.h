#ifndef __DGB__
#define __DGB__

#include <Windows.h>
#include <cstdio>

class Dbg
{
private:
	Dbg();
	~Dbg();

public:
	Dbg*	getDbg();
	void	print(const char* arg, ...);
	bool	fatalError(HWND _hWnd, LPCSTR msg);
};

#endif