#include "DynamicGameEntity.h"


DynamicGameEntity::DynamicGameEntity()
{
}


DynamicGameEntity::~DynamicGameEntity()
{
}

void DynamicGameEntity::Move(float _dt)
{
	mPosition.x += _dt * speed;
	mPosition.z += _dt * speed;
}
void DynamicGameEntity::Initialize(D3DManager* _d3dManager)
{
	GameEntity::Initialize( _d3dManager );
}