#ifndef __MATERIAL__
#define __MATERIAL__

class Material
{
public:
	Material(int _id, float _amb, float _spec, float _diff, float _shin);
	~Material();

	const int mId;
	const float mAmbient;
	const float mDiffuse;
	const float mSpecular;
	const float mShiny;
};

#endif