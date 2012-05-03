#ifndef __VERTEXBUFFER__
#define __VERTEXBUFFER__

#include <D3DX10.h>

class VertexBuffer
{
public:
	VertexBuffer(int _id);
	~VertexBuffer();

	const int mId;
	ID3D10Buffer* mBuffer;
	void setBuffer(ID3D10Buffer& _buf);
};

#endif