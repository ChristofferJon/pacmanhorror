#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include "fmod.h"
#include "fmod.hpp"
#include <Windows.h>

#include "CFG.h"
#include "SFXAsset.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

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
	FMOD::Channel* Channel0;
};

#endif