#include "Node.h"

int Node::count = 0;

Node::Node(float angle){

	id = count++;
	float x = cos(angle);
	float y = sin(angle);
	location = make_pair(x,y);
	//cout << "x, y = " << x << " " << y << endl;
}

