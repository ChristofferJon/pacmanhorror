#ifndef __GFS__
#define __GFS__

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "ResourceHandler.h"
#include "SkyBox.h"

#include "Camera.h"
#include "Graph.h"

#include "pacman.h"

class GFS
{
public:
	GFS(string _file);
	~GFS();

	void Update( float dt );
	void Draw( float dt );
	void Initialize( ResourceHandler* _resources );

public:
	vector<StaticGameEntity*> SGE;
	ResourceHandler* mResources;

	Camera* cam;
	D3DManager* md3dManager;
	ID3D10Device* md3dDevice;
	Graph*	quadtree;
	Node* root;
	pacman* p;
};

#endif