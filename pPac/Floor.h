#ifndef __FLOOR__
#define __FLOOR__

#include "StaticGameEntity.h"

class Floor : public StaticGameEntity
{
public:
	Floor();
	~Floor();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize();
};

#endif