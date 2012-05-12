#ifndef __WALL__
#define __WALL__

#include "StaticGameEntity.h"

class Wall : public StaticGameEntity
{
public:
	Wall();
	~Wall();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize();
};

#endif