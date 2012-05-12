#include "SkyBox.h"


SkyBox::SkyBox() : StaticGameEntity()
{

}

void SkyBox::Initialize()
{

}


SkyBox::~SkyBox()
{
}

void SkyBox::Update(float _dt)
{

}

void SkyBox::Draw(float _dt)
{
	// get model buffer
	md3dDevice->IASetVertexBuffers( 0, 1, &mModel->mBuffer->mBuffer, &mModel->mBuffer->stride, &mModel->mBuffer->offset );

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTranslation( &m, mPosition.x, mPosition.y, mPosition.z);

	//md3dManager->mBasicEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)&m);
	md3dManager->mWorldMatrixEffectVariable->SetMatrix(m);

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