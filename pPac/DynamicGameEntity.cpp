#include "DynamicGameEntity.h"


DynamicGameEntity::DynamicGameEntity()
{
}


DynamicGameEntity::~DynamicGameEntity()
{
}

void DynamicGameEntity::Move(float _dt)
{
	mPosition.x += _dt * speed[0];
	mPosition.z += _dt * speed[0];
}
void DynamicGameEntity::Initialize()
{
	GameEntity::Initialize();
}