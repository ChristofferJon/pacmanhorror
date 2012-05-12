#ifndef __WORLDGENERATOR__
#define __WORLDGENERATOR__

#include "StandardCalls.h"

#include "CFG.h"
#include "ResourceHandler.h"

#include <ios>
#include <iostream>
#include <fstream>

class GFS;

#include "GameEntity.h"
#include "Floor.h"
#include "Pill.h"
#include "Wall.h"
#include "pacman.h"

struct mLevelInfo
{
	int size;
	string file;
};

class WorldGenerator
{
public:
	WorldGenerator();
	~WorldGenerator();
	void Initialize( GFS* _gfs );

	void GenerateWorld();
	void LevelData( string file );
	void RAWLoader( string file );

	GFS* mGFS;
	ResourceHandler* mResources;
	CFG* mCFG;
	mLevelInfo mLI;
	vector<float> mapGrid;

	void PopulateStatics();
	void AddWall( float _x, float _y );
	void AddFloor( float _x, float _y );
	void AddPill( float _x, float _y );

	void PopulateDynamics();
	void AddPacman( float _x, float _y );

	void InstanceObject( GameEntity* GE );

	Dbg* mDbg;
};

#endif