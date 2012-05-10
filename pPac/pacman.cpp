#include "pacman.h"


pacman::pacman(Graph* _g)
{
	g = _g;
	listCounter = 1;
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.z = 0;
	wpp = 0;


	D3DXVECTOR3 temp = D3DXVECTOR3(128,0,128);
	destNode = g->getNode(temp.x, temp.z);
	
	currNode = g->getNode(mPosition.x, mPosition.z);

	wp.push_back(currNode);
	wp.push_back(destNode);


	path = g->findPath(currNode, destNode);
	
	for (int i = 0; i<3; i++)
	{
		 speed[i] = 20.0f;
	}

	
	nextNode = currNode;
}


pacman::~pacman()
{
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
				if (wpp < 2)
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

	Move(_dt, nextNode->pos); //Send in nextNode, so he will move towards the next node in list of all nodes


}

void pacman::Draw(float _dt)
{
	//do draw stuff here
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

