#ifndef DRTOPOLOGY_H
#define DRTOPOLOGY_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "Node.h"

using namespace std;

class DRTopology{
	void initNeighbours(Node* next, int k);
public:
	
	//derived fields
	int currentRadius;
	int targetRadius;
	vector<int> radii;

	//Base fields
	int numberOfNodes, noOfNbs;
	vector<Node*> topo;


	DRTopology(int n, int k, vector<int> radii);
	
	void becomeOptimal();
	void updateNbIDs(Node* current, Node* neighbour);
	void createDataSet();
	void plot();
	static bool pairCompare(const pair<int, float>& firstElem, const pair<int, float>& secondElem);

};
#endif