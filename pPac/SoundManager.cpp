#include "SoundManager.h"


SoundManager::SoundManager()
{
	int numChannels = 32;

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

		for each ( CFG_Entry* e in l->entries() )
		{
			if ( e->key() == "ID" )
				id = mCfg->getCFG()->GetIntOfKey( "ID", l->name(), d->name() );

			if ( e->key() == "FILE" )
			{
				directory = mCfg->getCFG()->GetStringOfKey( "FILE", l->name(), d->name() );

				if ( id >= 600 )
				{
					mSound.push_back( id );
					int index = mSound.size() - 1;
					mResult = mSystem->createSound( directory.c_str(), NULL, NULL, &mSound[index].mSound );
				}
				else
				{
					mMusic.push_back( id );
					int index = mMusic.size() - 1;
					mResult = mSystem->createSound( directory.c_str(), 0, NULL, & mMusic[index].mSound );
				}
			}
		}
	}
}

void SoundManager::PlaySound( int _id )
{
	FMOD::Sound* s = mSound[0].mSound;
	for each ( SFXAsset sa in mSound )
		if ( _id == sa.mId )
			s = sa.mSound;

	mResult = mSystem->playSound( FMOD_CHANNEL_FREE, s, false, &Channel0 );
}