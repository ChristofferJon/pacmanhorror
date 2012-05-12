#ifndef __SFXASSET__
#define __SFXASSET__

#include "fmod.h"
#include "fmod.hpp"

class SFXAsset
{
public:
	SFXAsset( int _id );
	~SFXAsset();

public:
	const int mId;
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;
};

#endif