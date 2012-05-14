#ifndef __PILL__
#define __PILL__

#include "StaticGameEntity.h"
#include "Camera.h"

class Pill : public StaticGameEntity
{
public:
	Pill();
	~Pill();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize(D3DManager* _d3dManager);
	Camera* cam;
};

#endif