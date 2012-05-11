#ifndef __RENDERPACKAGE__
#define __RENDERPACKAGE__

#include <D3DX10.h>

class RenderPackage
{
public:
	RenderPackage(int _id, ID3D10Effect* _effect, ID3D10EffectTechnique* _technique);
	~RenderPackage();

	const int mId;
	const ID3D10Effect* mEffect;
	ID3D10EffectTechnique* mTechnique;
};

#endif