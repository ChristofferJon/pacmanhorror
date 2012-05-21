#include "pacman.h"


pacman::pacman()
{

}


pacman::~pacman()
{
}

void pacman::Initialize(D3DManager* _d3dManager)
{
	DynamicGameEntity::Initialize( _d3dManager );

	cSpeed = 0.007f;
	cam->mPosition = mPosition;
	speed = WALK;
	battery = mHealth;
}


void pacman::walk( float dt )
{
	cam->walk( dt * speed );
}
void pacman::strafe( float dt )
{
	cam->strafe( dt * speed );
}
void pacman::Look( float dx, float dy )
{
	if ( ( cam->mLook.y >= -0.55 || dy < 0.0f ) && ( cam->mLook.y <= 0.55 || dy > 0.0f ))
		cam->pitch( dy * cSpeed );

	cam->rotateY( dx * cSpeed );
}

void pacman::UnLoadBattery( float charge )
{
	//battery -= charge;
}

void pacman::LoadBattery( float charge )
{
	battery += charge;

	mSfx->PlaySound( 602, 0.75f );
}

void pacman::Wound( float damage )
{
	//mHealth -= damage;

	mSfx->PlaySound( 604, 2.0f );
}

void pacman::Update(float _dt)
{
	for each ( GameEntityComponent* gec in GEC )
		gec->Update( _dt );

	mPosition = cam->mPosition;

	UnLoadBattery( 7.5 * _dt );

	if ( battery <= 0 )
		battery = 0;

	if ( battery <= 0 )
		Wound( 5.5f );

	if ( mHealth <= 0 )
		mHealth = 0;
}

void pacman::Draw(float _dt)
{
	float intensity = battery / 100.0f;
	if ( intensity > 1.0f )
		intensity = 1.0f;
	if ( intensity <= 0.1f )
		intensity = 0.1f;

	ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "intensity" );
	pVar->SetRawValue(&intensity, 0, sizeof(float));
}
