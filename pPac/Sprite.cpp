#include "Sprite.h"

Sprite::Sprite(int _id, Texture* _tex, VertexBuffer* _buf)
	: mId(_id), mTexture(_tex), mBuffer(_buf)
{

}


Sprite::~Sprite()
{
}
