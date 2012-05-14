#include "GFS.h"

GFS::GFS(string _file)
{

}


GFS::~GFS()
{
}

void GFS::Initialize( ResourceHandler* _resources )
{
	sLight = new SpotLight( D3DXVECTOR3( 0, 10, 0), D3DXVECTOR4( 0.5, 0.0, 0.0, 1.0 ), D3DXVECTOR3( 0, 0, 1 ) );
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
	ha = 100.0f;
}

void GFS::Update( float dt )
{
	p->Update( dt );
	//ChechForInput( dt );

	if ( cam->mPosition.y > 10 || cam->mPosition.y < 10 )
		cam->mPosition.y = 10;



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
					ha += 10;
					break;
				}

			break;
		}
	}

	for each ( GameEntity* ghost in mGhost )
		ghost->Update( dt );

	for each ( Ghost* g in mGhost )
	{
		float rPG = 200.0f;
		D3DXVECTOR3 lengthPG = p->mPosition - D3DXVECTOR3( g->mPosition.x + 200, 0, g->mPosition.z + 200);
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
		p->walk( dt );
	if (mInput->IsContinousKeyPress(DIK_S) )
		p->walk( -dt );
	if (mInput->IsContinousKeyPress(DIK_D) )
		p->strafe( dt );
	if (mInput->IsContinousKeyPress(DIK_A) )
		p->strafe( -dt );

	if ( mInput->IsContinousKeyPress(DIK_LSHIFT) )
		p->speed = RUN;
	else if ( mInput->IsContinousKeyPress(DIK_LCONTROL) )
		p->speed = SNEAK;
	else
		p->speed = WALK;

	float dx = mInput->getMousePos()->x - mInput->mOldMousePos.x;
	float dy = mInput->getMousePos()->y - mInput->mOldMousePos.y;

	p->Look( dx, dy );
}

void GFS::Draw( float dt )
{
	md3dDevice->OMSetDepthStencilState(0,0);
	sLight->position = -cam->mPosition;
	D3DXVECTOR3 dir = -cam->mLook;;
	//dir.x *= -1;

	// Light
	float h = 1.0f;
	ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "intensity" );
	pVar->SetRawValue(&h, 0, sizeof(float));
	md3dManager->mPtnEffect->GetVariableByName("direction")->AsVector()->SetFloatVector((float*)dir);

	md3dManager->mPtnEffect->GetVariableByName( "eye" )->AsVector()->SetFloatVector((float*)cam->mPosition);
	
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactor, 0xffffffff);


	md3dDevice->RSSetState( md3dManager->pRS );
	cam->rebuildView();

	for each ( GameEntity* floor in mFloor )
	{
		D3DXVECTOR3 length = floor->mPosition - cam->mPosition;
		float l = D3DXVec3Length( &length );
		float len = 100 / l;

		ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "dist" );
		pVar->SetRawValue(&len, 0, sizeof(float));

		floor->Draw( dt );
	}

	md3dManager->mPtnEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)cam->mView);
	for each ( GameEntity* wall in mWall )
	{
		D3DXVECTOR3 length = cam->mPosition - wall->mPosition;
		float l = D3DXVec3Length( &length );
		float len = 0;
		len = 500.0f / l;
		ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "dist" );
		pVar->SetRawValue(&len, 0, sizeof(float));

		wall->Draw( dt );
	}

	for each ( GameEntity* ghost in mGhost )
	{
		D3DXVECTOR3 length = cam->mPosition - ghost->mPosition;
		float l = D3DXVec3Length( &length );
		float len = 0;
		len = 500.0f / l;
		ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "dist" );
		pVar->SetRawValue(&len, 0, sizeof(float));

		ghost->Draw( dt );
	}

	md3dDevice->IASetInputLayout( md3dManager->mPtbLayout );

	for each ( GameEntity* pill in mPill )
		pill->Draw( dt );
}