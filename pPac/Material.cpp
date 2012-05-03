#include "Material.h"


Material::Material(int _id, float _amb, float _spec, float _diff, float _shin)	
		:	mId(_id), mAmbient(_amb), mDiffuse(_diff), mSpecular(_spec), mShiny(_shin)
{
}


Material::~Material()
{
}
