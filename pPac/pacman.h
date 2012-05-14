#pragma once

#include "DynamicGameEntity.h"
#include "Graph.h"
#include "Camera.h"

class pacman : public DynamicGameEntity
{
public:
	pacman();
	~pacman();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize(D3DManager* _d3dManager);

	void walk( float dt );
	void strafe( float dt );
	void Look( float dx, float dy );

	Camera* cam;

	float battery;
	float cSpeed;

	void LoadBattery( float charge );
};

