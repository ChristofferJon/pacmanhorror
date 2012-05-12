#include "SpotLight.h"

SpotLight::SpotLight( D3DXVECTOR3 _position, D3DXVECTOR4 _color, D3DXVECTOR3 _direction )
	: PointLight( _position, _color ), direction( _direction )
{
}

SpotLight::~SpotLight()
{
}
