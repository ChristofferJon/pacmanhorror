#include "Model.h"


Model::Model(int _id, Texture* _tex, VertexBuffer* _buf, Material* _mat, RenderPackage* _ren)
	:	mId(_id), mTexture(_tex), mBuffer(_buf), mMaterial(_mat), mRenderPackage(_ren)
{
}


Model::~Model()
{
}
