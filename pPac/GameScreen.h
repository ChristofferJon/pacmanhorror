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
	virtual void CheckForInput( float dt );

	GFS* mGFS;
	ResourceHandler* mResources;

	Event<Screen*> Return;
	int health;
	float h;
	int pi;
	int pOf;

public:
	void OnReturn( GameScreen* _me );


private:
	RECT mRec;

	string removeMe;
	string removeMeFPS;

	UINT FPS;
	DWORD frames;
	DWORD currentTime;
	DWORD lastUpdateTime;
	DWORD elapsedTime;
	string H;
	string gameOver;
	string pills;
};

#endif