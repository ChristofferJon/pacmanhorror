#include "Logic.h"


Logic::Logic(string _level, int mapSize)
{
	root = new Node(0,0, mapSize, mapSize);
	graph = new Graph(root);
	
	paused = true;
	updateWP = false;


}


Logic::~Logic()
{
}


void Logic::frame()
{
	//update timers

	//update other logic
}

void Logic::pauseControl()
{
	if(!paused)
	{
		paused = true;
		//stop timers
	}
	else
	{
		paused = false;
		//start timers
	}
}

int Logic::getNodeID(D3DXVECTOR3 _v)
{
	Node* temp = NULL;
	int res = 0;

	temp = graph->getNode(_v.x, _v.z);

	try
	{
		res = temp->ID;
	}
	catch(std::exception e)
	{
		res = -1;
	}
	temp = NULL;
	return res;
}