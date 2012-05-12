#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight( D3DXVECTOR3 _position, D3DXVECTOR4 _color );
	~PointLight();

	D3DXVECTOR4 color;
};

#endif