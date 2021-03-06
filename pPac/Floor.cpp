#include "Floor.h"


Floor::Floor() : StaticGameEntity()
{
}


Floor::~Floor()
{
}

void Floor::Initialize(D3DManager* _d3dManager)
{
	StaticGameEntity::Initialize(_d3dManager);
}

void Floor::Update( float dt )
{

}

void Floor::Draw( float dt )
{
	md3dDevice->IASetInputLayout( mModel->mRenderPackage->mLayout );

	// get model buffer
	md3dDevice->IASetVertexBuffers( 0, 1, &mModel->mBuffer->mBuffer, &mModel->mBuffer->stride, &mModel->mBuffer->offset );

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTranslation( &m, mPosition.x, mPosition.y, mPosition.z);

	//md3dManager->mBasicEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)&m);
	mModel->mRenderPackage->mEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)&m);

	mModel->mRenderPackage->mEffect->GetVariableByName("TEXTURE")->AsShaderResource()->SetResource( mModel->mTexture->pSRView );

	ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "material" );
	pVar->SetRawValue(&mat, 0, sizeof(aMaterial));
	

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