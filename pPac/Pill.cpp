#include "Pill.h"


Pill::Pill(void)
{
}


Pill::~Pill(void)
{
}

void Pill::Initialize(D3DManager* _d3dManager)
{
	StaticGameEntity::Initialize(_d3dManager);
}

void Pill::Update( float dt )
{

}

void Pill::Draw( float dt )
{
	md3dDevice->IASetInputLayout( mModel->mRenderPackage->mLayout );
	mModel->mRenderPackage->mEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((float*)cam->mView);

	// get model buffer & texture
	md3dDevice->IASetVertexBuffers( 0, 1, &mModel->mBuffer->mBuffer, &mModel->mBuffer->stride, &mModel->mBuffer->offset );
	mModel->mRenderPackage->mEffect->GetVariableByName("TEXTURE")->AsShaderResource()->SetResource( mModel->mTexture->pSRView );

	// translate & billboard object towards the camera
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTranslation( &m, mPosition.x, mPosition.y, mPosition.z);

	D3DXMATRIX ori (	cam->mRight.x,		cam->mRight.y,		cam->mRight.z,		0,
						cam->mUp.x,			cam->mUp.y,			cam->mUp.z,			0,
						cam->mLook.x,		cam->mLook.y,		cam->mLook.z,		0,
						0,					0,					0,					1 );
	m = ori * m;
	mModel->mRenderPackage->mEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)m );

	// get rendering technique
	ID3D10EffectTechnique* mTech = mModel->mRenderPackage->mTechnique;
	D3D10_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0);
		md3dDevice->Draw( mModel->mBuffer->numVertices, 0 );
	}
}