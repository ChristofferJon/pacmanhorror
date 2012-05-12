#include "SoundManager.h"


SoundManager::SoundManager()
{
	int numChannels = 32;
	
	mChannels.push_back( chanMenuS );
	mChannels.push_back( chanMenuM );
	mChannels.push_back( chanGameS );
	mChannels.push_back( chanGameM );
	mChannels.push_back( chanGhost );
	mChannels.push_back( chanPac );

	for ( int i = 0; i < mChannels.size(); i++)
		mChannels[i] = NULL;

	mSystem = NULL;
	mResult = FMOD::System_Create( &mSystem );
	mSystem->init( numChannels, FMOD_INIT_NORMAL, 0 );

	Initialize();
}


SoundManager::~SoundManager()
{
}

void SoundManager::Initialize()
{
	DATA_CONTAINER* d = mCfg->getCFG()->GetContainer( "SoundResources" );

	for each ( CFG_Link* l in d->links() )
	{
		int id = -1;
		string directory = "INVALID";
		int channel = -1;

		for each ( CFG_Entry* e in l->entries() )
		{
			if ( e->key() == "ID" )
				id = mCfg->getCFG()->GetIntOfKey( "ID", l->name(), d->name() );
			if ( e->key() == "FILE" )
				directory = mCfg->getCFG()->GetStringOfKey( "FILE", l->name(), d->name() );

			if ( e->key() == "CHANNEL" )
			{
				channel = mCfg->getCFG()->GetIntOfKey( "CHANNEL", l->name(), d->name() );

				if ( id >= 600 )
				{
					mSound.push_back( id );
					int index = mSound.size() - 1;
					mResult = mSystem->createSound( directory.c_str(), NULL, NULL, &mSound[index].mSound );
					mSound[index].mChannel = mChannels[channel];
				}
				else
				{
					mMusic.push_back( id );
					int index = mMusic.size() - 1;
					mResult = mSystem->createSound( directory.c_str(), 0, NULL, & mMusic[index].mSound );
					mMusic[index].mChannel = mChannels[channel];
				}
			}
		}
	}
}

void SoundManager::PlaySound( int _id )
{
	FMOD::Sound* s = mSound[0].mSound;
	FMOD::Channel* c = mChannels[0];
	for each ( SFXAsset sa in mSound )
		if ( _id == sa.mId )
		{
			s = sa.mSound;
			c = sa.mChannel;
		}

	mResult = mSystem->playSound( FMOD_CHANNEL_FREE, s, false, &c );
}