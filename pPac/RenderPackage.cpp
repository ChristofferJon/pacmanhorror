#include "RenderPackage.h"


RenderPackage::RenderPackage(int _id, ID3D10Effect* _effect, ID3D10EffectTechnique* _technique) 
	:	mId(_id), mEffect(_effect), mTechnique(_technique)
{
}


RenderPackage::~RenderPackage()
{
}
