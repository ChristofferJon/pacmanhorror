#include "pacman.h"


pacman::pacman(Graph* _g)
{
	g = _g;
	
}


pacman::~pacman()
{
}

void pacman::Initialize()
{
	listCounter = 1;
	//mPosition.x = -2000;
	//mPosition.y = 0;
	//mPosition.z = -2000;
	wpp = 0;


	//D3DXVECTOR3 temp = D3DXVECTOR3(2400,0,-200);
	destNode = g->getNode(temp.x, temp.z);
	
	currNode = g->getNode(mPosition.x+200, mPosition.z+200 );

	wp.push_back(currNode);
	wp.push_back(destNode);

	path = g->findPath(currNode, destNode);
	
	for (int i = 0; i<3; i++)
	{
		 speed[i] = 500.0f;
	}
	
	nextNode = currNode;

	hurting = true;
}


void pacman::Update(float _dt)
{

	//do update stuff here
	float deltaX = nextNode->pos.x - this->mPosition.x;
	float deltaZ = nextNode->pos.z - this->mPosition.z; //checks distance towards next node he will enter

	
	if ((std::abs((double)deltaX) < 10.0f && std::abs((double)deltaZ) < 10.0f)) //if distance is less than 10
	{
		if ((int)path.size() > listCounter)
		{
			if (nextNode->ID == wp[wpp]->ID)
			{
				path.clear();
				wpp++;
				if (wpp < wp.size() )
				{
					path = g->findPath(nextNode, wp[wpp]);
				}
				listCounter = 1;
			}

			listCounter++;
			
			currNode = nextNode;
			if(listCounter < path.size())
			{
				nextNode = path[listCounter];
			}				
		}
	}
	else if ( nextNode == path[path.size() - 1] )
	{
		wp.push_back( g->getNode( cam->mPosition.x, cam->mPosition.z ) );
	}

	Move(_dt, nextNode->pos); //Send in nextNode, so he will move towards the next node in list of all nodes
}

void pacman::Draw(float _dt)
{
	md3dDevice->IASetInputLayout( mModel->mRenderPackage->mLayout );
	// get model buffer
	md3dDevice->IASetVertexBuffers( 0, 1, &mModel->mBuffer->mBuffer, &mModel->mBuffer->stride, &mModel->mBuffer->offset );

	mModel->mRenderPackage->mEffect->GetVariableByName("TEXTURE")->AsShaderResource()->SetResource( mModel->mTexture->pSRView );

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTranslation( &m, mPosition.x+200, mPosition.y- 150, mPosition.z +200);

	D3DXVECTOR3 targetTransformed = D3DXVECTOR3( currNode->pos.x, currNode->pos.y, currNode->pos.z );
	D3DXVECTOR3 rP = mPosition -targetTransformed;

	D3DXMATRIX rotY;
	D3DXVECTOR3 rY = D3DXVECTOR3(0,1,0);
	float ang = std::atan2(rP.x, rP.z);

	D3DXMatrixRotationAxis(&rotY, &rY, ang);

	//m = rotY * m;

	mModel->mRenderPackage->mEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((float*)&m);

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

void pacman::Move(float _dt, D3DXVECTOR3 goal)
{
	//Move pacman according to position relative to goals position
	if (this->mPosition.x < goal.x)
	{
		this->mPosition.x += this->speed[0] * _dt;
	}
	else if (this->mPosition.x > goal.x)
	{
		this->mPosition.x -= this->speed[0] * _dt;
	}

	if (this->mPosition.z < goal.z)
	{
		this->mPosition.z += this->speed[0] * _dt;
	}
	else if (this->mPosition.z > goal.z)
	{
		this->mPosition.z -= this->speed[0] * _dt;
	}
}

int pacman::getCurrNodeID()
{
	return this->currNode->ID;
}

int pacman::getDestNodeID()
{
	return this->destNode->ID;
}

int pacman::getNextNodeID()
{
	return this->nextNode->ID;
}

float pacman::getPacmanPosX()
{
	return this->mPosition.x;
}

float pacman::getPacmanPosZ()
{
	return this->mPosition.z;
}

