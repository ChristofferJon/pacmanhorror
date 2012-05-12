#ifndef __PTNVERTEX__
#define __PTNVERTEX__

#include "Vertex.h"

class PTNVertex : public Vertex
{
public:
	PTNVertex( D3DXVECTOR3 _position, D3DXVECTOR3 _normal, D3DXVECTOR2 _texCoord );
	~PTNVertex();

	D3DXVECTOR3 normal;
	D3DXVECTOR2 texCoord;
};

#endif