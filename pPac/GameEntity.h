#ifndef __GAMEENTITY__
#define __GAMEENTITY__

#include <D3DX10.h>
#include "Model.h"

class GameEntity
{
public:
	GameEntity();
	~GameEntity();

	struct aMaterial
	{
		float ambient, diffuse, specular, shininess;
	};

public:
	float mHealth;
	D3DXVECTOR3 mPosition;
	Model* mModel;
	D3DManager* md3dManager;
	ID3D10Device* md3dDevice;

public:
	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;
	virtual void Initialize(D3DManager* _d3dManager, ...);
	aMaterial mat;
};

#endif