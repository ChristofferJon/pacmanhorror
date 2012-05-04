#pragma once

#include <vector>
#include <Windows.h>
#include <D3DX10.h>

using std::vector;

class Node
{
public:
	Node();
	Node(float _upperLeftX, float _upperLeftZ, float _width, float _height);
	~Node();
	void setWeight(int _weight);
	void addEdge(Node* _Node);
	Node* getNeighbour(int _dir, int _num);
	HRESULT SubDivide();

	D3DXVECTOR3			pos;
	Node*				neighbours[4][6];
	vector<Node*>		edges;
	Node**				subNode;
	float				upperLeftX, upperLeftZ, width, height;
	int					ID, weight, originNode, totalWeight;
	bool				visited;
};

