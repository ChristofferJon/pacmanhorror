#ifndef __GFS__
#define __GFS__

#include "StandardCalls.h"

#include "ResourceHandler.h"
#include "SkyBox.h"
#include "InputManager.h"

#include "Camera.h"
#include "WorldGenerator.h"

#include <math.h>

#include "SoundManager.h"

#include "pacman.h"
#include "Graph.h"
#include "LightCollection.h"

class GFS
{
public:
	GFS(string _file);
	~GFS();

	void Update( float dt );
	void Draw( float dt );
	void Initialize( ResourceHandler* _resources );
	void ChechForInput( float dt );

public:
	vector<StaticGameEntity*> mWall;
	vector<StaticGameEntity*> mFloor;
	vector<StaticGameEntity*> mPill;

	ResourceHandler* mResources;

	Camera* cam;
	D3DManager* md3dManager;
	ID3D10Device* md3dDevice;
	InputManager* mInput;

	WorldGenerator mWorld;
	SoundManager* mSoundManager;

	Graph* quadtree;
	Node* root;
	pacman* p;
	Dbg* mDgb;

	bool oldHurt;
	D3DXVECTOR3 oldPos;
	SpotLight* sLight;
};

#endif