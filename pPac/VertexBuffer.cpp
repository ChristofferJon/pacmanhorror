#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(int _id) : mId(_id)
{

}


VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::setBuffer(ID3D10Buffer& _buf)
{
	mBuffer = &_buf;
}