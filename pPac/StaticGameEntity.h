
E:\Programmering\Github\pacmanhorror>@git.exe %*
#ifndef __STATICGAMEENTITY__
#define __STATICGAMEENTITY__

#include "GameEntity.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity();
	~StaticGameEntity();

	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;
	virtual void Initialize() = 0;
};

#endif
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
