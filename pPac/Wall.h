#ifndef __WALL__
#define __WALL__

#include "SpotLight.h"

#include "StaticGameEntity.h"

struct mate
{
	float ambient, diffuse, specular, shininess;
};

class Wall : public StaticGameEntity
{
public:
	Wall();
	~Wall();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	virtual void Initialize();

	SpotLight* sLight;
	mate* ma;
};

#endif