#include "PTVertex.h"


PTVertex::PTVertex( D3DXVECTOR3 _position, D3DXVECTOR2 _texCoord )
	: Vertex( _position ), texCoord( _texCoord )
{
}


PTVertex::~PTVertex(void)
{
}
