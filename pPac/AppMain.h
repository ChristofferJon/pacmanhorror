#ifndef __APPMAIN__
#define __APPMAIN__

#include <cstdlib>
#include "D3DManager.h"
#include "CFG.h"

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
	bool		Initialize();
	void		Update();

private:
	D3DManager*	mD3DManager;
	CFG*		mCfg;
};

#endif