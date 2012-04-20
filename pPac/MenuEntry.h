#ifndef __MENUENTRY__
#define __MENUENTRY__

#include <string>

using std::string;

class MenuEntry
{
public:
	MenuEntry(string _text);
	~MenuEntry();

private:
	const string	mText;
	float			mSelectionFade;

public:
	void		Update();
	void		Draw();
};

#endif