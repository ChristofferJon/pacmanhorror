#include "GameEntity.h"


GameEntity::GameEntity()
{
}


GameEntity::~GameEntity()
{
}

void GameEntity::Initialize()
{

	mat.ambient = mModel->mMaterial->mAmbient;
	mat.diffuse = mModel->mMaterial->mDiffuse;
	mat.shininess = mModel->mMaterial->mShiny;
	mat.specular = mModel->mMaterial->mSpecular;
}