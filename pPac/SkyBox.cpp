#include "SkyBox.h"


SkyBox::SkyBox() : StaticGameEntity()
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
	md3dDevice->IASetVertexBuffers( 0, 1, &mModel->mBuffer->mBuffer, &mModel->mBuffer->offset, &mModel->mBuffer->stride );
	md3dDevice->IASetInputLayout( md3dManager->mBasicLayout );

	D3D10_TECHNIQUE_DESC techDesc;

	ID3D10EffectTechnique* mTech = mModel->mRenderPackage->mTechnique;
	mTech->GetDesc(&techDesc);

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTranslation( &m, mPosition.x, mPosition.y, mPosition.z );

	md3dManager->mWorldMatrixEffectVariable->SetMatrix(m);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0);
		md3dDevice->Draw( 36, 0);
	}
}