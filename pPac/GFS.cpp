
E:\Programmering\Github\pacmanhorror>@git.exe %*
#include "GFS.h"

GFS::GFS(string _file)
{

}


GFS::~GFS()
{
}

void GFS::Initialize( ResourceHandler* _resources )
{
	mResources = _resources;
	md3dDevice = md3dManager->mD3DDevice;
	cam = new Camera( md3dManager );

	mWorld = WorldGenerator();
	mWorld.Initialize( this );
	mWorld.LevelData( "Level1" );
	mWorld.PopulateStatics();


	//md3dManager->mBasicEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)&cam->mProj);
	md3dManager->mProjectionMatrixEffectVariable->SetMatrix(cam->mProj);
	md3dManager->mPtbEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((float*)cam->mProj);
}

void GFS::Update( float dt )
{
	ChechForInput( dt );
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

	if ( cam->mPosition.y > 0 || cam->mPosition.y < 0 )
		cam->mPosition.y = 0;

	for each ( GameEntity* pill in mPill )
	{
		float rad = 150.0f;
		D3DXVECTOR3 length = cam->mPosition - pill->mPosition;
		float len = abs(D3DXVec3Length(  &length  ));
		
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
}

void GFS::Draw( float dt )
{
	md3dDevice->RSSetState( md3dManager->pRS );
	cam->rebuildView();

	//md3dManager->mBasicEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)&cam->mView);
	md3dManager->mViewMatrixEffectVariable->SetMatrix(cam->mView);

	md3dDevice->IASetInputLayout( md3dManager->mBasicLayout );
	for each ( GameEntity* floor in mFloor )
		floor->Draw( dt );

	for each ( GameEntity* wall in mWall )
		wall->Draw( dt );

	md3dDevice->IASetInputLayout( md3dManager->mPtbLayout );

	for each ( GameEntity* pill in mPill )
		pill->Draw( dt );
}
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
