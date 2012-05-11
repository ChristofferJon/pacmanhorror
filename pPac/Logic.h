#pragma once
 
#include "Graph.h"

using std::string;

class Logic
{

private:

	Node*		root;
	//Timer
	//Sounds?
	bool paused;
	bool updateWP; //might not be needed

public:
	Graph*		graph;

	Logic(string _level, int mapSize);
	Logic();
	void frame();
	void pauseControl();
	int getNodeID(D3DXVECTOR3 _v);
	
	~Logic(void);
};

