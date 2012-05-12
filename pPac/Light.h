#ifndef __LIGHT__
#define __LIGHT__

#include <D3DX10.h>

class Light
{
public:
	Light( D3DXVECTOR3 _position );
	~Light();

	D3DXVECTOR3 position;
};

#endif