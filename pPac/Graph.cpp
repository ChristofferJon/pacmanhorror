#include "Graph.h"


Graph::Graph(Node* _root)
{
	root = _root;
	counter = 0;

	for (int i = 0; i < 5; i++)
	{
		_root->SubDivide();
	}

	addToList(_root);
	removeDuplicates();	
	sort();
	gridder();
	setNeighbours();

	nodeList.shrink_to_fit();
}

Graph::~Graph()
{
}

#pragma region Init

void Graph::removeDuplicates()
{
	for (int i = 0; i < (int)tempNodeList.size(); i++)
	{
		for (int j = 0; j < (int)tempNodeList.size(); j++)
		{
			if (tempNodeList[i]->upperLeftX == tempNodeList[j]->upperLeftX && tempNodeList[i]->upperLeftZ == tempNodeList[j]->upperLeftZ)
			{
				tempNodeList.erase(tempNodeList.begin() + j);
			}			
		}
	}
}

void Graph::addToList(Node* _root)
{
	for (int i = 0; i < 4; i++)
	{
		if (_root->subNode != NULL)
		{
			addToList(_root->subNode[i]);
		} 
		else
		{
			tempNodeList.push_back(_root);
		}
	}
}

void Graph::gridder()
{
	int widthCounter = 0;
	int width =  (int)std::sqrt((double)nodeList.size());

	for (int i = 0; i < (int)nodeList.size(); i++)
	{
		if (i + 1 < (int)nodeList.size() && nodeList[i + 1] != NULL && widthCounter < width - 1)
		{
			nodeList[i] ->addEdge(nodeList[i + 1]);
		}

		if (i - 1 > -1 && nodeList[i - 1] != NULL && widthCounter != 0)
		{
			nodeList[i] ->addEdge(nodeList[i - 1]);
		}

		if (i + width < (int)nodeList.size() && nodeList[i + width] != NULL)
		{
			nodeList[i] ->addEdge(nodeList[i + width]);
		}

		if (i - width > -1 && nodeList[i - width] != NULL)
		{
			nodeList[i] ->addEdge(nodeList[i - width]);
		}
		widthCounter++;

		if (widthCounter == width)
		{
			widthCounter = 0;
		}
	}

	/*
	Kopplings schema:

	#	3	#
	1	*	0
	#	2	#

	*/
}

void Graph::sort()
{
	Node* temp2 = NULL;
	vector<Node*> tempList;

	for (int i = 0; i < (int)tempNodeList.size(); i++)
	{
		for (int j = 0; j < (int)tempNodeList.size(); j++)
		{
			if (tempNodeList[i]->upperLeftZ < tempNodeList[j]->upperLeftZ)
			{
				Node* temp = tempNodeList[i];
				tempNodeList[i] = tempNodeList[j];
				tempNodeList[j] = temp;
			}
		}
	}

	temp2 = tempNodeList[0];

	for (int i = 0; i < (int)tempNodeList.size(); i++)
	{
		if (tempNodeList[i]->upperLeftZ == temp2->upperLeftZ)
		{
			tempList.push_back(tempNodeList[i]);
		} 
		else
		{
			temp2 = tempNodeList[i];
			i--;
			sortHelper(tempList);	
			tempList.clear();
		}

		if (i == tempNodeList.size() - 1)
		{
			sortHelper(tempList);
		}
	}

	for (int i = 0; i < (int)nodeList.size(); i++)
	{
		nodeList[i]->ID = i;
	}
}

void Graph::sortHelper(vector<Node*> _tempList)
{
	for (int j = 0; j < (int)_tempList.size(); j++)
	{
		for (int k = 0; k < (int)_tempList.size(); k++)
		{
			if (_tempList[j]->upperLeftX < _tempList[k]->upperLeftX)
			{
				Node* temp = _tempList[j];
				_tempList[j] = _tempList[k];
				_tempList[k] = temp;
			}
		}
	}

	for (int j = 0; j < (int)_tempList.size(); j++)
	{
		nodeList.push_back(_tempList[j]);
	}	
}

void Graph::setNeighbours()
{
	for (int j = 0; j < (int)nodeList.size(); j++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 6; k++)
			{
				nodeList[j]->neighbours[i][k] = nodeList[j]->getNeighbour(i,k);
			}
		}
	}

}

#pragma endregion 

vector<Node*> Graph::findPath(Node* _startNode, Node* _targetNode)
{
	retRoute.clear();

	for (int i = 0; i < (int)nodeList.size(); i++)
	{
		nodeList[i]->visited = false;
		nodeList[i]->totalWeight = -1;
		nodeList[i]->originNode = -1;
	}	

	openNodes.push_back(_startNode);
	_startNode->totalWeight = 0;	

	while(!openNodes.empty())
	{
		_startNode = openNodes[0];

		for(int i = 1; i < (int)openNodes.size(); i++)
		{
			if(openNodes[i]->totalWeight < _startNode->totalWeight)
			{
				_startNode = openNodes[i];
			}
		}

		algorithm(_startNode);

		if(_startNode->ID == _targetNode->ID)
		{
			break;
		}
	}

	while(_startNode->originNode != -1)
	{
		retRoute.push_back(_startNode);
		_startNode = nodeList[_startNode->originNode];
	}

	retRoute.push_back(_startNode);
	std::reverse(retRoute.begin(), retRoute.end());
	openNodes.clear();
	return retRoute;
}

void Graph::algorithm(Node* _currentNode)
{
	for(int i = 0; i < (int)_currentNode->edges.size(); i++)
	{
		if(!_currentNode->edges[i]->visited)
		{
			int temp = _currentNode->totalWeight + _currentNode->edges[i]->weight;

			if(_currentNode->edges[i]->totalWeight < 0 || temp < _currentNode->edges[i]->totalWeight)
			{
				_currentNode->edges[i] -> originNode = _currentNode -> ID;
				_currentNode->edges[i] -> totalWeight = temp;				
				openNodes.push_back(_currentNode -> edges[i]);
			}
		}
	}
	_currentNode->visited = true;
	
	openNodes.erase(std::remove(openNodes.begin(), openNodes.end(), _currentNode),openNodes.end());
}

Node* Graph::getNode(float _x, float _z)
{
	//try
	//{
		for (int i = 0; i < 4; i++)
		{
			float left = root->subNode[i]->upperLeftX;
			float right = root->subNode[i]->upperLeftX + root->subNode[i]->width;
			float top = root->subNode[i]->upperLeftZ;
			float bottom = root->subNode[i]->upperLeftZ + root->subNode[i]->height;

			if (_x < right + 1.0f && _x > left - 1.0f && _z < bottom + 1.0f && _z > top - 1.0f)
			{
				return getNode(root->subNode[i], _x, _z);
			}
		}
	/*}
	catch(exception e)
	{
		return NULL;
	}*/

	
}

Node* Graph::getNode(Node* _root, float _x, float _z)
{
	for (int i = 0; i < 4; i++)
	{
		if (_root->subNode != NULL)
		{
			float left = _root->subNode[i]->upperLeftX;
			float right = _root->subNode[i]->upperLeftX + _root->subNode[i]->width;
			float top = _root->subNode[i]->upperLeftZ;
			float bottom = _root->subNode[i]->upperLeftZ + _root->subNode[i]->height;

			if (_x < right + 1.0f && _x > left - 1.0f && _z < bottom + 1.0f && _z > top - 1.0f)
			{
				return getNode(_root->subNode[i], _x, _z);
			}
		}
		else
		{
			return _root;
		}
	}		
}

Node* Graph::getNode(int nodeID)
{
	return nodeList[nodeID];
}