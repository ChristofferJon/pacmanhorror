#include "pacman.h"


pacman::pacman()
{

}


pacman::~pacman()
{
}

void pacman::Initialize()
{
	currentSpeed = 500.0f;
	cSpeed = 0.007f;
	cam->mPosition = mPosition;
	speed = WALK;
}


void pacman::Update(float _dt)
{
	currentSpeed = speed;
	mPosition = cam->mPosition;
}

void pacman::Draw(float _dt)
{

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