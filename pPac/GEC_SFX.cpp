#include "GEC_SFX.h"


GEC_SFX::GEC_SFX() : GameEntityComponent()
{
}


GEC_SFX::~GEC_SFX()
{
}

void GEC_SFX::Initialize( ... )
{

}

void GEC_SFX::Initialize( SoundManager* _sound )
{
	mSoundManager = _sound;
	timeDelay = 0;
	timeThreshold = 1.0f;
	canPlay = true;
}

void GEC_SFX::Update( float dt )
{
	timeDelay += dt;
	if ( timeDelay >= timeThreshold )
	{
		timeDelay = 0;
		canPlay = true;
	}
}

void GEC_SFX::PlaySound( int id, float _threshold )
{
	if ( canPlay )
	{
		mSoundManager->PlaySound( id );
		canPlay = false;
	}
}