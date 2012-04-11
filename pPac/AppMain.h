#ifndef __APPMAIN__
#define __APPMAIN__

#include <cstdlib>
#include "Parser.h"
#include "D3DManager.h"

/*
Treated as a singleton since we'll only
need one instance during the entire duration
of the application
*/

class AppMain
{
public:
	AppMain();
	~AppMain();

public:
	bool		Initialize(Parser* _parser);
	void		Update();

private:
	Parser*		mParser;
	D3DManager*	mD3DManager;
};

#endif