#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight( D3DXVECTOR3 _position, D3DXVECTOR4 _color, D3DXVECTOR3 _direction );
	~SpotLight();

	D3DXVECTOR3 direction;
};

#endif