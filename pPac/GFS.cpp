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
	SGE.push_back( new SkyBox( ) );
	SGE[0]->mModel = mResources->getModel( 801 );
	SGE[0]->mPosition = D3DXVECTOR3( 0, 0, 200 );
	SGE[0]->md3dManager = md3dManager;
	SGE[0]->md3dDevice = md3dManager->mD3DDevice;

	cam = new Camera( md3dManager );
	cam->mPosition = D3DXVECTOR3( 0, 0, -200 );

	root = new Node(0,0, 256, 256);
	quadtree = new Graph(root);

	p = new pacman(quadtree);
	//initializera pacman och ett spöke
	//set pacmans mål till spökets position

	md3dDevice = md3dManager->mD3DDevice;
}

void GFS::Draw( float dt )
{
	md3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	

	md3dDevice->OMSetDepthStencilState( 0, 0);

	//float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	//md3dDevice->OMSetBlendState(0, blendFactor, 0xffffffff);

	cam->rebuildView();
	/*D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	md3dManager->mWorldMatrixEffectVariable->SetMatrix(m);*/

	md3dManager->mProjectionMatrixEffectVariable->SetMatrix( cam->mProj );

	md3dManager->mViewMatrixEffectVariable->SetMatrix( cam->mView );

	for each ( GameEntity* g in SGE )
		g->Draw( dt );

	md3dDevice->RSSetState( md3dManager->pRS );
}

void GFS::Update( float _dt)
{
	//do update stuff here!
	//move pacman towards his goal.

	p->Update(_dt);
}