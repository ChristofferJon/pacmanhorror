#ifndef __RENDERPACKAGE__
#define __RENDERPACKAGE__

#include <D3DX10.h>

class RenderPackage
{
public:
	RenderPackage(int _id, ID3D10Effect* _effect, ID3D10EffectTechnique* _technique, ID3D10InputLayout* _layout);
	~RenderPackage();

	const int mId;
	ID3D10Effect* mEffect;
	ID3D10EffectTechnique* mTechnique;
	ID3D10InputLayout* mLayout;
};

#endif