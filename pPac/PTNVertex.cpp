#include "PTNVertex.h"


PTNVertex::PTNVertex( D3DXVECTOR3 _position, D3DXVECTOR3 _normal, D3DXVECTOR2 _texCoord )
	: Vertex( _position ), normal( _normal ), texCoord( _texCoord )
{
}


PTNVertex::~PTNVertex(void)
{
}
