#include "WorldGenerator.h"
#include "GFS.h"

WorldGenerator::WorldGenerator()
{
}


WorldGenerator::~WorldGenerator()
{
}

void WorldGenerator::Initialize( GFS* _gfs )
{
	mGFS = _gfs;
	mResources = mGFS->mResources;
	md3dManager = mGFS->md3dManager;
}

void WorldGenerator::RAWLoader( string file )
{
	UINT gridSize = mLI.size * mLI.size;
	vector<unsigned char> in ( gridSize );
	std::ifstream inFile;

	inFile.open( mLI.file, std::ios_base::binary);

	if ( inFile )
	{
		inFile.read( (char*)&in[0], (std::streamsize)in.size() );
		inFile.close();
	}
	else
		mDbg->print( "%s failed to load\n", mLI.file );

	mapGrid.resize( gridSize, 0 );

	for ( UINT i = 0; i < gridSize; ++i)
		mapGrid[i] = (float)in[i];
}

// placement of SGE's
void WorldGenerator::PopulateStatics()
{
	// divide the levelInfo.size
	// set x o y to negative, centering the
	// map around origo by going from -bound to +bound
	float bounds = mLI.size / 2;
	float x = -bounds;
	float y = -bounds;
	float cellSize = 200.0f;

	/*
		0-63	: reserved
		64-95	: wall
		96+		: floor
		129-160	: PacSpawn
		161-192	: GhostSpawn
		193-224	: Pill
		224+	: Boost
	*/
	for ( int i = 0; i < mapGrid.size(); i++ )
	{
		if ( mapGrid[i] <= 64 )
		{
			mGFS->quadtree->getNode( x * cellSize, y * cellSize  )->setWeight( INT_MAX );
		}
		if ( mapGrid[i] >= 64 && mapGrid[i] < 96)
		{
			AddWall( x * cellSize, y * cellSize );

			mGFS->quadtree->getNode( x * cellSize, y * cellSize  )->setWeight( INT_MAX );
		}
		if ( mapGrid[i] >= 96 )
		{
			AddFloor( x * cellSize, y * cellSize );
		}
		if ( mapGrid[i] > 192 && mapGrid[i] <= 224 )
		{
			AddPill( x * cellSize, y * cellSize );
		}

		x++;
		if ( x >= bounds )
		{
			x = -bounds;
			y++;
		}
		if ( y >= bounds )
			y = -bounds;
	}
}

void WorldGenerator::AddPill( float _x, float _y )
{
	Pill* pill = new Pill();
	pill->cam = mGFS->cam;
	pill->mPosition = D3DXVECTOR3( _x, -75, _y );
	pill->mModel = mResources->getModel( 802 );
	pill->Initialize( md3dManager );

	mGFS->mPill.push_back( pill );
}

void WorldGenerator::AddFloor( float _x, float _y )
{
	Floor* floor = new Floor();
	floor->mPosition = D3DXVECTOR3( _x, -100, _y );
	floor->mModel = mResources->getModel( 801 );
	floor->Initialize( md3dManager );

	mGFS->mFloor.push_back( floor );
}

void WorldGenerator::AddWall( float _x, float _y )
{
	Wall* wall = new Wall();
	wall->sLight = mGFS->sLight;
	wall->mPosition = D3DXVECTOR3( _x, 0, _y );
	wall->mModel = mResources->getModel( 804 );
	wall->Initialize(md3dManager);

	mGFS->mWall.push_back( wall );
}

void WorldGenerator::PopulateDynamics()
{
	int x[] = { -2200, 1400, -200, -1200 };
	int y[] = { -1400, 1800, -600, 1200 };
	D3DXVECTOR3 dest[] = {	D3DXVECTOR3( 2000, 0, 2000 ),
							D3DXVECTOR3( 1000, 0, 200 ),
							D3DXVECTOR3( -800, 0, 600 ),
							D3DXVECTOR3( -1800, 0, -1600 ) };

	AddPacman( 2400.0f, 0 );

	for ( int i = 0; i < 4; i++)
		AddGhost( x[i], y[i], dest[i] );
}

void WorldGenerator::AddGhost( float _x, float _y, D3DXVECTOR3 _dest )
{
	Ghost* ghost = new Ghost( mGFS->quadtree ); 
	mGFS->mGhost.push_back( ghost );

	ghost->pacM = mGFS->mPacMan;
	ghost->temp = _dest;
	ghost->mModel = mResources->getModel( 805 );
	ghost->mPosition = D3DXVECTOR3( _x, 0, _y );
	ghost->Initialize( md3dManager );
}

void WorldGenerator::AddPacman( float _x, float _y )
{
	pacman* pac = new pacman();
	pac->cam = mGFS->cam;
	pac->mPosition = D3DXVECTOR3( _x, 0, _y );
	pac->mModel = mResources->getModel( 805 );
	pac->Initialize( md3dManager );

	mGFS->mPacMan = pac;
}

void WorldGenerator::InstanceObject( GameEntity* GE )
{
	GE->Initialize(mGFS->md3dManager );
}

void WorldGenerator::LevelData( string file )
{
	mCFG->getCFG()->MapDirectories( ".\\Levels\\", "MapCollection.dat" );
	mCFG->getCFG()->ReadFromFile( ".\\Levels\\", file );
	DATA_CONTAINER* d = mCFG->getCFG()->GetContainer( file );
	

	mLI.size = mCFG->getCFG()->GetIntOfKey( "SIZE", d->getLink( "LEVELINFO" )->name(), file );
	mLI.file = mCFG->getCFG()->GetStringOfKey( "FILE", d->getLink( "LEVELINFO" )->name(), file );

	RAWLoader( "HELLO" );
}