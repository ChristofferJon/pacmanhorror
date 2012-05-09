#ifndef __MENUSCREEN__
#define __MENUSCREEN__

#include "screen.h"
#include "MenuEntry.h"
#include "Sprite.h"
#include <vector>
using std::vector;
using std::string;

#include "event.h"

//ta väck sen
#include "ResourceHandler.h"

struct sv
{
	float topLeft[2];
	float dimensions[2];
	float opacity;
};

class MenuScreen : public Screen
{
public:
	MenuScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~MenuScreen();

public:
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Initialize( ResourceHandler* _resources );
	virtual void CheckForInput();

protected:
	vector<MenuEntry*> mMenuEntries;
	ResourceHandler* rc;
	Sprite* mSprite;
	RenderPackage* mRP;
	void OnSelectEntry(int _index);
	int selectedEntry;
private:
	
	bool Intersect( int _index, POINT* _mousePos );
	RECT mRec;
};

#endif