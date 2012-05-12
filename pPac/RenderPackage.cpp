#include "RenderPackage.h"


RenderPackage::RenderPackage(int _id, ID3D10Effect* _effect, ID3D10EffectTechnique* _technique, ID3D10InputLayout* _layout) 
	:	mId(_id), mEffect(_effect), mTechnique(_technique), mLayout( _layout )
{
}


RenderPackage::~RenderPackage()
{
}
