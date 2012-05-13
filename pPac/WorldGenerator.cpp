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
	Pill* p = new Pill();
	p->cam = mGFS->cam;
	mGFS->mPill.push_back( p );
	int index = mGFS->mPill.size() - 1;

	mGFS->mPill[index]->mPosition = D3DXVECTOR3( _x, -75, _y );
	mGFS->mPill[index]->mModel = mResources->getModel( 802 );
	InstanceObject( mGFS->mPill[index] );
}

void WorldGenerator::AddFloor( float _x, float _y )
{
	Floor* f = new Floor();
	mGFS->mFloor.push_back( f );
	int index = mGFS->mFloor.size() - 1;

	mGFS->mFloor[index]->mPosition = D3DXVECTOR3( _x, -100, _y );
	mGFS->mFloor[index]->mModel = mResources->getModel( 801 );
	InstanceObject( mGFS->mFloor[index] );
}

void WorldGenerator::AddWall( float _x, float _y )
{
	Wall* w = new Wall();
	w->sLight = mGFS->sLight;
	mGFS->mWall.push_back( w );
	int index = mGFS->mWall.size() - 1;

	mGFS->mWall[index]->mPosition = D3DXVECTOR3( _x, 0, _y );
	mGFS->mWall[index]->mModel = mResources->getModel( 804 );
	InstanceObject( mGFS->mWall[index] );
}

void WorldGenerator::PopulateDynamics()
{
	int x[] = { -2200, 1400, -200, -1200 };
	int y[] = { -1400, 1800, -600, 1200 };
	D3DXVECTOR3 dest[] = {	D3DXVECTOR3( 2000, 0, 2000 ),
							D3DXVECTOR3( 1000, 0, 200 ),
							D3DXVECTOR3( -800, 0, 600 ),
							D3DXVECTOR3( -1800, 0, -1600 ) };

	for ( int i = 0; i < 4; i++)
		AddPacman( x[i], y[i], dest[i] );
}

void WorldGenerator::AddPacman( float _x, float _y, D3DXVECTOR3 _dest )
{
	pacman* p = new pacman( mGFS->quadtree ); 
	mGFS->mGhost.push_back( p );

	p->cam = mGFS->cam;
	p->temp = _dest;
	p->mModel = mResources->getModel( 805 );
	p->mPosition = D3DXVECTOR3( _x, 0, _y );
	InstanceObject( p );
}

void WorldGenerator::InstanceObject( GameEntity* GE )
{
	GE->md3dManager = mGFS->md3dManager;
	GE->md3dDevice = mGFS->md3dDevice;
	GE->Initialize();
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