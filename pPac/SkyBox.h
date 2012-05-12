#ifndef __SKYBOX__
#define __SKYBOX__

#include "StaticGameEntity.h"

class SkyBox : public StaticGameEntity
{
public:
	SkyBox();
	~SkyBox();

public:
	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize();
};

#endif