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
	virtual void Initialize();
};

#endif