#ifndef BTTOPOLOGY_H
#define BTTOPOLOGY_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "BTNode.h"

using namespace std;

class BTTopology{
	
	void initNeighbours(BTNode* next, int k);
	int getDistance(int a, int b);

public:
	
	//Base fields
	int numberOfNodes, noOfNbs;
	vector<BTNode*> topo;

	BTTopology(int n, int k);
	
	void becomeOptimal();
	void updateNbIDs(BTNode* current, BTNode* neighbour);
	void createDataSet();
	void plot();
	static bool pairCompare(const pair<int, int>& firstElem, const pair<int, int>& secondElem);

};
#endif