#ifndef __GAMETIMER__
#define __GAMETIMER__

#include <Windows.h>

class GameTimer
{
private:
	GameTimer();
	~GameTimer();

public:
	GameTimer*	getInstance();
	float	gameTime()const;
	float	deltaTime()const;

	void	reset();
	void	start();
	void	stop();
	void	tick();

private:
	double	mSecondsPerCount;
	double	mDeltaTime;

	__int64	mBaseTime;
	__int64	mPausedTime;
	__int64	mStopTime;
	__int64	mPrevTime;
	__int64	mCurrentTime;

	bool	mStopped;
};

#endif