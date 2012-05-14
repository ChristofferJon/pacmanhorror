#pragma once

#include "DynamicGameEntity.h"
#include "Graph.h"
#include "Camera.h"

enum SPEED
{
	SNEAK = 100,
	WALK = 500,
	RUN = 900
};


class pacman : public DynamicGameEntity
{
public:
	pacman();
	~pacman();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize();

	void walk( float dt );
	void strafe( float dt );
	void Look( float dx, float dy );

	Camera* cam;

	float currentSpeed;
	float cSpeed;
	SPEED speed;
};

