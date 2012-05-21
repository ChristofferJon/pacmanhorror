#include "Node.h"

Node::Node()
{
	upperLeftX = 0;
	upperLeftZ = 0;
	width = 0;
	height = 0;
	subNode = NULL;
	ID = -1;
	pos.x = upperLeftX;
	pos.y = 1.0f;
	pos.z = upperLeftZ;
	originNode = -1;
	totalWeight = 1;
	weight = 1;
	visited = false;
	edges.clear();
}

Node::Node(float _upperLeftX, float _upperLeftZ, float _width, float _height)
{
	upperLeftX = _upperLeftX;
	upperLeftZ = _upperLeftZ;
	width = _width;
	height = _height;
	subNode = NULL;
	ID = 0;
	pos.x = upperLeftX;
	pos.y = 1.0f;
	pos.z = upperLeftZ;
	originNode = -1;
	totalWeight = -1;
	weight = 1;
	visited = false;
	edges.clear();
}

Node::~Node()
{
}

HRESULT Node::SubDivide()
{
	HRESULT result = S_OK;

	if(!subNode)
	{
		float w = width/2;
		float h = height/2;
		float ulx = upperLeftX;
		float uly = upperLeftZ;

		subNode = (Node**)::CoTaskMemAlloc(4 * sizeof(Node*));
		subNode[0] = new Node(ulx, uly, w, h);
		subNode[1] = new Node(ulx + w, uly, w, h);
		subNode[2] = new Node(ulx, uly + h, w, h);
		subNode[3] = new Node(ulx + w, uly + h, w, h);
	}
	else
	{
		for(int i = 0; i < 4 && SUCCEEDED(result); i++)
		{
			result = subNode[i]->SubDivide();
		}
	}
	return result;
}

void Node::setWeight(int _weight)
{
	weight = _weight;
}

void Node::addEdge(Node* _Node)
{
	edges.push_back(_Node);
}

Node* Node::getNeighbour(int _dir, int _num)
{
	if (_num == 0 && (int)edges.size() > _dir)
	{
		return edges[_dir];
	}
	else if ((int)edges.size() <= _dir)
	{
		return NULL;
	}
	else
	{
		_num--;
		getNeighbour(_dir, _num);
	}
	return NULL;
}


