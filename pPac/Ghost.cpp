#include "Ghost.h"


Ghost::Ghost(Graph* _g)
{
	g = _g;
}


Ghost::~Ghost()
{
}

void Ghost::Initialize(D3DManager* _d3dManager)
{
	DynamicGameEntity::Initialize(_d3dManager);
	listCounter = 1;
	wpp = 0;

	//destNode = g->getNode(temp.x, temp.z);
	//
	//currNode = g->getNode(mPosition.x+200, mPosition.z+200 );

	//wp.push_back(currNode);
	//wp.push_back(destNode);

	
	currNode = g->getNode(mPosition.x, mPosition.z );
	destNode = g->getNode(pacM->mPosition.x, pacM->mPosition.z);
	//nextNode = currNode;
	path = g->findPath(currNode, destNode);
	hurting = true;
	speed = JOG;
	counter = 1;
	nextNode = path[counter];
}

void Ghost::Update(float _dt)
{
	//do update stuff here
	float deltaX = nextNode->pos.x - this->mPosition.x;
	float deltaZ = nextNode->pos.z - this->mPosition.z; //checks distance towards next node he will enter

	// srsly you guiz!
	if ((std::abs((double)deltaX) < 10.0 && std::abs((double)deltaZ) < 10.0)) //if distance is less than 10
	{
		counter++;
		if ( counter < path.size() )
		{
			nextNode = path[counter];
		}
	}
	if ( nextNode == destNode )
	{
		path.clear();
		counter = 1;

		currNode = g->getNode( mPosition.x, mPosition.z );
		destNode = g->getNode( pacM->mPosition.x, pacM->mPosition.z);

		if ( destNode->weight <= 1 )
		{
			path = g->findPath(currNode, destNode);
			counter++;
			nextNode = path[counter];
		}
	}

	Move(_dt, nextNode->pos); //Send in nextNode, so he will move towards the next node in list of all nodes
}

void Ghost::Draw(float _dt)
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

	ID3D10EffectVariable* pVar = md3dManager->mPtnEffect->GetVariableByName( "material" );
	pVar->SetRawValue(&mat, 0, sizeof(aMaterial));

	m = rotY * m;

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

void Ghost::Move(float _dt, D3DXVECTOR3 goal)
{
	//Move pacman according to position relative to goals position
	if (this->mPosition.x < goal.x - 10.0f)
	{
		this->mPosition.x += this->speed * _dt;
	}
	else if (this->mPosition.x > goal.x)
	{
		this->mPosition.x -= this->speed * _dt;
	}

	if (this->mPosition.z < goal.z - 10.0f)
	{
		this->mPosition.z += this->speed * _dt;
	}
	else if (this->mPosition.z > goal.z)
	{
		this->mPosition.z -= this->speed * _dt;
	}
}

int Ghost::getCurrNodeID()
{
	return this->currNode->ID;
}

int Ghost::getDestNodeID()
{
	return this->destNode->ID;
}

int Ghost::getNextNodeID()
{
	return this->nextNode->ID;
}

float Ghost::getPacmanPosX()
{
	return this->mPosition.x;
}

float Ghost::getPacmanPosZ()
{
	return this->mPosition.z;
}

