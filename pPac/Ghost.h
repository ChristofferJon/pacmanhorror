#pragma once

#include "DynamicGameEntity.h"

class Ghost : public DynamicGameEntity
{
public:
	Ghost();
	~Ghost();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
};

