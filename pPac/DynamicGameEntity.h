#pragma once

#include "GameEntity.h"

class DynamicGameEntity : public GameEntity
{
public:
	DynamicGameEntity();
	~DynamicGameEntity();

	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;

protected:
	int mLives;
	float speed[3]; //array of Speeds
	int mIDSFX[10]; //array with sounds, should maybe be dynamic. 10 is just a placeholdung number.
	/*
	Not defined in overview.

	mDeltaPosition; //move-function?
	mRender;		//render function?
	mCollission;	//collission check?
	mSFX;			//sound managing?
	*/
public:
	virtual void Move(float _dt);
};

