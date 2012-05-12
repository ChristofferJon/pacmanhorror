#ifndef __VERTEX__
#define __VERTEX__

#include <D3DX10.h>

class Vertex
{
public:
	Vertex( D3DXVECTOR3 _position );
	~Vertex();

protected:
	D3DXVECTOR3 position;
};

#endif