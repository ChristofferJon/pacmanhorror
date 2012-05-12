#ifndef __PTVERTEX__
#define __PTVERTEX__

#include "Vertex.h"

class PTVertex : public Vertex
{
public:
	PTVertex( D3DXVECTOR3 _position, D3DXVECTOR2 _texCoord );
	~PTVertex();

	D3DXVECTOR2 texCoord;
};

#endif