#include "GameTimer.h"

GameTimer* instance = NULL;

GameTimer::GameTimer()	:	mSecondsPerCount( 0.0 ),
							mDeltaTime( -1.0 ),
							mPausedTime( 0 ),
							mPrevTime( 0 ),
							mCurrentTime( 0 ),
							mStopped( false )
{
	__int64 countsPerSec;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}


GameTimer::~GameTimer()
{
}

GameTimer* GameTimer::getInstance()
{
	if (instance == NULL)
		instance = new GameTimer();

	return instance;
}

float GameTimer::gameTime()const
{
	// make sure we don't count time after stopped
	if ( mStopped )
		return (float)( (mStopTime - mBaseTime)*mSecondsPerCount );
	else	// subtract pausedTime from currentTime
		return (float) ( ((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount );

}

float GameTimer::deltaTime()const
{
	return (float)mDeltaTime;
}

void GameTimer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter( (LARGE_INTEGER*)&currTime );

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::start()
{
	__int64 startTime;
	QueryPerformanceCounter( (LARGE_INTEGER*)&startTime );

	if ( mStopped )
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::stop()
{
	if ( !mStopped )
	{
		__int64 currTime;
		QueryPerformanceCounter( (LARGE_INTEGER*)&currTime );

		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::tick()
{
	if ( mStopped )
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter( (LARGE_INTEGER*)&currTime );
	mCurrentTime = currTime;

	// time difference between current and old frame
	mDeltaTime = (mCurrentTime - mPrevTime)*mSecondsPerCount;

	mPrevTime = mCurrentTime;

	//safety guard for negative time
	if ( mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}