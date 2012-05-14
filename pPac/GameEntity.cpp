#include "GameEntity.h"


GameEntity::GameEntity()
{
}


GameEntity::~GameEntity()
{
}

void GameEntity::Initialize(D3DManager* _d3dManager, ...)
{
	md3dManager = _d3dManager;
	md3dDevice = md3dManager->mD3DDevice;
	mHealth = 100.0f;

	this->mat.ambient = mModel->mMaterial->mAmbient;
	mat.diffuse = mModel->mMaterial->mDiffuse;
	mat.shininess = mModel->mMaterial->mShiny;
	mat.specular = mModel->mMaterial->mSpecular;
}