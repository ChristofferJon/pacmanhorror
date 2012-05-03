#ifndef __MODEL__
#define __MODEL__

#include <D3DX10.h>

#include "Texture.h"
#include "VertexBuffer.h"
#include "Material.h"
#include "RenderPackage.h"

class Model
{
public:
	Model(int _id, Texture* _tex, VertexBuffer* _buf, Material* _mat, RenderPackage* _ren);
	~Model();

	const int mId;
	const Texture* mTexture;
	const VertexBuffer* mBuffer;
	const Material* mMaterial;
	const RenderPackage* mRenderPackage;
};

#endif