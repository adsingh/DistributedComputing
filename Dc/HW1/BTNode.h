#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;


class BTNode{

	public:
		

		static int count;
		
		int id;

		BTNode(int x,int y);

		vector<int> nbIds;

		pair<int, int> location;


};
#endif