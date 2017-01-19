#include "BTNode.h"

int BTNode::count = 1;

BTNode::BTNode(int x, int y){

	id = count++;
	location = make_pair(x,y);
	//cout << "x, y = " << x << " " << y << endl;
}

