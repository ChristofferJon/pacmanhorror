#include "PCVertex.h"


PCVertex::PCVertex( D3DXVECTOR3 _position, D3DXVECTOR4 _color )
	: Vertex( _position ), color( _color )
{
}


PCVertex::~PCVertex()
{
}
