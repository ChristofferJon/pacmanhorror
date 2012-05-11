#pragma once

#include "Node.h"
#include <iostream>
#include <algorithm>


class Graph
{
private:

	void createEdge(int vectorPos1, int vectorPos2, int weight);
	void algorithm(Node* currentNode);
	void removeDuplicates();
	void addToList(Node* _root);
	void gridder();
	void sort();
	void sortHelper(vector<Node*> _templist);
	Node* getNode(Node* _root, float _x, float _z);

	vector<Node*> openNodes, tempNodeList, retRoute;
	int			counter, numberOfSubDivides;
	Node*		targetNode, currentNode;
	Node*		root;

public:
	Graph(Node* _root);
	~Graph();
	vector<Node*> findTotPath(vector<Node*> _waypoints);
	vector<Node*> findPath(Node* _startNode, Node* _targetNode);

	Node* getNode(float _x, float _z);
	void setNeighbours();
	vector<Node*> nodeList;
	Node* getNode(int nodeID);

};

