#ifndef __PCVERTEX__
#define __PCVERTEX__

#include "Vertex.h"

class PCVertex : public Vertex
{
public:
	PCVertex( D3DXVECTOR3 _position, D3DXVECTOR4 _color);
	~PCVertex();

	D3DXVECTOR4 color;
};

#endif