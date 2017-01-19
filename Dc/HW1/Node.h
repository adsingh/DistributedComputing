#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;


class Node{

	public:
		

		static int count;
		int id;

		Node(float angle);

		vector<int> nbIds;

		pair<float, float> location;


};
#endif