#ifndef __STATIC_GAMEENTITY__
#define __STATIC_GAMEENTITY__

#include "GameEntity.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity();
	~StaticGameEntity();

	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;
};

#endif