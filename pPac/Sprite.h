#ifndef __SPRITE__
#define __SPRITE__

#include "Texture.h"
#include "VertexBuffer.h"

class Sprite
{
public:
	Sprite(int _id, Texture* _tex, VertexBuffer* _buf);
	~Sprite();

	const int mId;
	VertexBuffer* mBuffer;
	const Texture* mTexture;
};

#endif