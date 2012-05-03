#ifndef __SCREENMEDIATOR__
#define __SCREENMEDIATOR__

class ScreenManager;
class Screen;

class ScreenMediator
{
public:
	ScreenMediator(ScreenManager* _screenManager);
	~ScreenMediator();

	ScreenManager* mScreenManager;

	void RemoveMe( Screen* _screen);
	void RemoveAll();
	void AddNewScreen( Screen* _screen );
};

#endif