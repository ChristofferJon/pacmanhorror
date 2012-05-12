#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include "fmod.h"
#include "fmod.hpp"
#include <Windows.h>

#include "CFG.h"
#include "SFXAsset.h"

#include "StandardCalls.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

public:
	FMOD::System* mSystem;
	FMOD_RESULT mResult;

	void Initialize();
	void LoadSound( );
	CFG* mCfg;

	vector<SFXAsset> mSound;
	vector<SFXAsset> mMusic;

	void PlaySound( int _id );
	FMOD::Channel* chanMenuS;
	FMOD::Channel* chanMenuM;
	FMOD::Channel* chanGameS;
	FMOD::Channel* chanGameM;

	FMOD::Channel* chanGhost;
	FMOD::Channel* chanPac;

	vector<FMOD::Channel*> mChannels;
};

#endif