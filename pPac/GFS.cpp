#include "GFS.h"

GFS::GFS(string _file)
{

}


GFS::~GFS()
{
}

void GFS::Initialize( ResourceHandler* _resources )
{
	sLight = new SpotLight( D3DXVECTOR3( 0, 100, 0), D3DXVECTOR4( 0.5, 0.0, 0.0, 1.0 ), D3DXVECTOR3( 0, -1, 0 ) );
	mResources = _resources;
	md3dDevice = md3dManager->mD3DDevice;
	cam = new Camera( md3dManager );
	//cam->mPosition.x = 0;
	//cam->mPosition.z = 1000;
	root = new Node(-3200, -3200, 6400, 6400);
	quadtree = new Graph(root);

	mWorld = WorldGenerator();
	mWorld.Initialize( this );
	mWorld.LevelData( "Level1" );
	mWorld.PopulateStatics();


	//md3dManager->mBasicEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)&cam->mProj);
	md3dManager->mProjectionMatrixEffectVariable->SetMatrix(cam->mProj);
	md3dManager->mPtbEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)cam->mProj);
	md3dManager->mPtnEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)cam->mProj);

	//p = new pacman(quadtree);
	mWorld.PopulateDynamics();
	//initializera pacman och ett spöke
	//set pacmans mål till spökets position

	hurting = false;
	oldHurt = false;
	playOnce = true;
	delay = 0;
}

void GFS::Update( float dt )
{
	//ChechForInput( dt );

	if ( cam->mPosition.y > 0 || cam->mPosition.y < 0 )
		cam->mPosition.y = 0;

	for each ( GameEntity* wall in mWall )
	{
		float rad = 120.0f;
		D3DXVECTOR3 length = cam->mPosition - wall->mPosition;
		float len = abs( D3DXVec3Length( &length ) );

		if ( len <= rad )
		for ( int i = 0; i < mWall.size(); i++ )
				if ( wall == mWall[i] )
				{
					D3DXVECTOR3 temp = D3DXVECTOR3( oldPos.x - cam->mPosition.x, 10, oldPos.z - cam->mPosition.z);
					cam->mPosition += temp;
				}
	}

	for each ( GameEntity* pill in mPill )
	{
		float rad = 150.0f;
		D3DXVECTOR3 length = cam->mPosition - pill->mPosition;
		float len = abs( D3DXVec3Length( &length ) );
		
		if ( len <= rad )
		{
		for ( int i = 0; i < mPill.size(); i++ )
				if ( pill == mPill[i] )
				{
					mPill.erase( mPill.begin() + i );
					mPill.shrink_to_fit();
					mSoundManager->PlaySound( 602 );
					break;
				}
			break;
		}
	}

	for each ( GameEntity* ghost in mGhost )
		ghost->Update( dt );

	for each ( pacman* p in mGhost )
	{
		float rPG = 200.0f;
		D3DXVECTOR3 lengthPG = cam->mPosition - D3DXVECTOR3( p->mPosition.x + 200, 0, p->mPosition.z + 200);
		float lenPG = abs( D3DXVec3Length( &lengthPG ) );

		if ( lenPG < rPG )
		{
			D3DXVECTOR3 temp = D3DXVECTOR3( oldPos.x - cam->mPosition.x, 10, oldPos.z - cam->mPosition.z);
			//cam->mPosition += temp;
		}
		if ( lenPG < rPG && hurting == false)
		{
			hurting = true;
			break;
		}
		else if ( lenPG > rPG * 2 && hurting == true )
		{
			hurting = false;	
		}
	}

	if ( hurting != oldHurt && playOnce == true )
	{
			mSoundManager->PlaySound( 604 );
			mSoundManager->PlaySound( 607 );

			playOnce = false;
	}

	delay += dt;
	if ( delay >= 3 )
	{
		playOnce = true;
		delay = 0;
	}

	oldHurt = hurting;

	oldPos = cam->mPosition;
}

void GFS::ChechForInput( float dt )
{
	float speed = 500 * dt;

	if (mInput->IsContinousKeyPress(DIK_W) )
		cam->walk( speed );
	if (mInput->IsContinousKeyPress(DIK_S) )
		cam->walk( -speed );
	if (mInput->IsContinousKeyPress(DIK_D) )
		cam->strafe( speed );
	if (mInput->IsContinousKeyPress(DIK_A) )
		cam->strafe( -speed );

	if ( mInput->isMLeftButton() )
	{
		float cSpeed = 0.015f;
		float dx = mInput->getMousePos()->x - mInput->mOldMousePos.x;
		float dy = mInput->getMousePos()->y - mInput->mOldMousePos.y;

		cam->pitch(dy * cSpeed);
		cam->rotateY(dx * cSpeed);
	}
}

void GFS::Draw( float dt )
{
	md3dDevice->RSSetState( md3dManager->pRS );
	cam->rebuildView();

	//md3dManager->mBasicEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)&cam->mView);
	md3dManager->mViewMatrixEffectVariable->SetMatrix(cam->mView);

	//md3dDevice->IASetInputLayout( md3dManager->mBasicLayout );
	for each ( GameEntity* floor in mFloor )
		floor->Draw( dt );

	//md3dDevice->IASetInputLayout( md3dManager->mPtbLayout );
	md3dManager->mPtnEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)cam->mView);
	for each ( GameEntity* wall in mWall )
		wall->Draw( dt );

	for each ( GameEntity* ghost in mGhost )
		ghost->Draw( dt );

	md3dDevice->IASetInputLayout( md3dManager->mPtbLayout );

	for each ( GameEntity* pill in mPill )
		pill->Draw( dt );
}