#ifndef __TEST__
#define __TEST__

class ScreenManager;

class Screen;

class TEST
{
public:
	TEST(Screen* _screen);
	~TEST(void);

	ScreenManager* sm;
};

#endif