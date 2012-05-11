#ifndef __GameScreen__
#define __GameScreen__

#include "Screen.h"
#include "GFS.h"
#include "ResourceHandler.h"

class GameScreen : public Screen
{
public:
	GameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~GameScreen();

protected:
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Initialize( ResourceHandler* _resources );
	virtual void CheckForInput();

	GFS* mGFS;
	ResourceHandler* mResources;

private:
	RECT mRec;

	string removeMe;
	string removeMeFPS;
	string removeMeCamPos;
	string removeMeCamLook;
	string removeMeBox;
	string pString;
	string destString;
	string nextString;
	string stringX;
	string stringZ;

	UINT FPS;
	DWORD frames;
	DWORD currentTime;
	DWORD lastUpdateTime;
	DWORD elapsedTime;
};

#endif