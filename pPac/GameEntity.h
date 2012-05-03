#ifndef __GAMEENTITY__
#define __GAMEENTITY__

#include <D3DX10.h>
#include "Model.h"

class GameEntity
{
public:
	GameEntity();
	~GameEntity();

protected:
	float mHealth;
	D3DXVECTOR3 mPosition;
	Model* mModel;

public:
	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;
};

#endif