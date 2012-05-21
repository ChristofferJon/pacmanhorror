#ifndef __GEC_SFX__
#define __GEC_SFX__

#include "GameEntityComponent.h"
#include "SoundManager.h"

class GEC_SFX : public GameEntityComponent
{
public:
	GEC_SFX();
	~GEC_SFX();

	virtual void Initialize( ... );
	virtual void Initialize( SoundManager* _sound );
	virtual void Update( float dt );

	SoundManager* mSoundManager;
	float timeDelay;
	float timeThreshold;
	bool canPlay;

	void PlaySound( int id, float _threshold );
};

#endif