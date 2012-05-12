#include "PointLight.h"


PointLight::PointLight( D3DXVECTOR3 _position, D3DXVECTOR4 _color )
	: Light( _position ), color( _color )
{
}


PointLight::~PointLight()
{
}
