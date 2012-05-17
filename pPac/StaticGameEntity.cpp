#include "StaticGameEntity.h"


StaticGameEntity::StaticGameEntity() : GameEntity()
{
}


StaticGameEntity::~StaticGameEntity()
{
}

void StaticGameEntity::Initialize(D3DManager* _d3dManager)
{
	GameEntity::Initialize(_d3dManager);
}