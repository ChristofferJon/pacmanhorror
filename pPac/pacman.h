#pragma once

#include "DynamicGameEntity.h"
#include "Graph.h"

class pacman : public DynamicGameEntity
{
public:
	pacman(Graph* _g);
	~pacman();

	virtual void Update(float _dt);
	virtual void Draw(float _dt);
	void Move(float _dt, D3DXVECTOR3 goal);
	int getCurrNodeID();
	int getDestNodeID();
	int getNextNodeID();
	float getPacmanPosX();
	float getPacmanPosZ();

private:
	Graph* g;
	Node* currNode;
	Node* destNode, *nextNode;
	int wpp, currWP, listCounter, ID;
	vector<Node*> wp, path;
};

