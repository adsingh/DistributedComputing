#include "BTTopology.h"

BTTopology::BTTopology(int n, int k)
{
	cout << "Hi\n";
	numberOfNodes = n;
	noOfNbs = k;
	int x =0,y=0, xF = 0;
	int power, index = 1;
	int incr=0;
	for(int i = 1 ; i <= numberOfNodes; i++){
		//cout << "angle = " << angle << endl;
		//cout << "x, y = " << x << ' ' << y << endl;
		BTNode* next =  new BTNode(x , y);
		//srand(time(NULL)-1);
		initNeighbours(next, i);
		topo.push_back(next);
		power = pow(2,index);
		if(i+1 == power){
			y--;
			index++;
			incr = power/(-2);
		}
		x = incr++;
		if(incr == 0){
			incr++;
		}

	}
	for(int i = 0 ; i < noOfNbs ; i++){
		cout << topo[3]->nbIds[i] << ' ';
	}
	cout << endl;
	cout << "Init finished\n";
}

void BTTopology::initNeighbours(BTNode* next, int myID){

	for(int i = 0 ; i < noOfNbs ; i++){
		int id = (int)(((((double)std::rand()) / RAND_MAX) * numberOfNodes+1));
		//cout << "id = " << id << endl;
		if(id == myID){
			i--;
			continue;
		}
		next->nbIds.push_back(id);
	}
}

//void printNeighbours()
void BTTopology::becomeOptimal(){

	int count = 1;
	for(int i = 0; i < 50 ; i++){

		BTNode* current;
		for(int n = 0; n < numberOfNodes ; n++){
			int randomId;
			int currentNbId;
			current  = topo[n];
			//randomId = (int)(((((double)std::rand()) / RAND_MAX) * noOfNbs));
			//cout << randomId << " random\n";
			do
			{
				randomId = (int)(((((double)std::rand()) / RAND_MAX) * noOfNbs));
				//cout << randomId << " random\n";
				currentNbId = current->nbIds[randomId];
			}while(currentNbId-1 == n);
			BTNode* neighbour =  topo[currentNbId-1];
			//cout << "updating\n";
			updateNbIDs(current, neighbour);
			//cout << endl;

		}
	}
}

void BTTopology::updateNbIDs(BTNode* current, BTNode* neighbour){

	/*cout << "before: current size = " << current->nbIds.size() << " neighbour size = " << neighbour->nbIds.size() << "\n";
	for(int i = 0; i < current->nbIds.size() ; i++){
		cout << current->nbIds[i] << ' ';
	}
	cout << endl;
	for(int i = 0; i < neighbour->nbIds.size() ; i++){
		cout << neighbour->nbIds[i] << ' ';
	}
	cout << endl;*/
	vector<pair<int, int> > v1, v2;
	current->nbIds.insert(current->nbIds.end(), neighbour->nbIds.begin(), neighbour->nbIds.end());
	sort(current->nbIds.begin(), current->nbIds.end());
	int dist;
	vector<int>::iterator it;
	int prev = -1;
	for(it = current->nbIds.begin(); it != current->nbIds.end(); it++){
		if(it != current->nbIds.begin() && *it == prev)
			continue;
		dist = getDistance(current->id, *it);
		v1.push_back(make_pair(*it, dist));
		dist = getDistance(neighbour->id, *it);
		v2.push_back(make_pair(*it, dist));
		prev = *it;
	}
	//sort(v1.begin(), v1.end(), [](pair<int, float> x, pair<int, float>  y) { return x.second < y.second; });
	//sort(v2.begin(), v2.end(), [](pair<int, float> x, pair<int, float>  y) { return x.second < y.second; });
	sort(v1.begin(), v1.end(), pairCompare);
	sort(v2.begin(), v2.end(), pairCompare);
	//v1.resize(noOfNbs);
	//v2.resize(noOfNbs);
	current->nbIds.clear();
	neighbour->nbIds.clear();
	//current->nbIds.push_back(v1[0].first);
	//neighbour->nbIds.push_back(v2[0].first);
	for(int i = 0 ;i < v1.size(); i++){
		//if(v1[i].first != current->nbIds[i-1])
		
		if(v1[i].first != current->id)
			current->nbIds.push_back(v1[i].first);
		if(current->nbIds.size() == noOfNbs)
			break;
		//if(v2[i].first != neighbour->nbIds[i-1])
			
	}
	for(int i = 0 ;i < v2.size(); i++){
		//if(v1[i].first != current->nbIds[i-1])
		if(v2[i].first != neighbour->id)
			neighbour->nbIds.push_back(v2[i].first);
		if(neighbour->nbIds.size() == noOfNbs)
			break;
		//if(v2[i].first != neighbour->nbIds[i-1])
			
	}

	/*cout << "after: current size = " << current->nbIds.size() << " neighbour size = " << neighbour->nbIds.size() << "\n";
	for(int i = 0; i < current->nbIds.size() ; i++){
		cout << current->nbIds[i] << ' ';
	}
	cout << endl;
	for(int i = 0; i < neighbour->nbIds.size() ; i++){
		cout << neighbour->nbIds[i] << ' ';
	}
	cout << endl;*/
}


int BTTopology::getDistance(int a, int b) {
	
	//cout << "a = , b = " << a << ' ' << b << endl;
	int bits = 32;
	int alevel=bits;
	int blevel=bits;
	int commonprefix=0;
	int mask = 1 << bits-1;
	// find the level of node a
	while((mask & a) == 0 ){
		a <<= 1;
		alevel--;
	}
	// find the level of node b
	while( (mask & b) == 0 ){
		b <<= 1;
		blevel--;
	}
	int length = alevel < blevel ? alevel : blevel;
	while((mask & ~(a ^ b)) != 0 && length>0){
		b <<= 1;
		a <<= 1;
		commonprefix++;
		length--;
	}
	return alevel - commonprefix + blevel - commonprefix;
}


void BTTopology::createDataSet(){

	//cout << "inside dataset\n";
	ofstream dataFile("data.txt");
	for(int i = topo.size() -1 ; i > -1 ; i--){
		int nb;
		for(int j = 0 ; j < noOfNbs; j++){
			dataFile << topo[i]->location.first << ' ' << topo[i]->location.second << endl;
			nb = topo[i]->nbIds[j];
			dataFile << topo[nb-1]->location.first << ' ' << topo[nb-1]->location.second << endl << endl;
		}
	}
	dataFile.close();
}

void BTTopology::plot(){
	//cout << "MAKING SYSCALL\n";
	system("gnuplot mine");

}

bool BTTopology::pairCompare(const pair<int, int>& firstElem, const pair<int, int>& secondElem){
	return firstElem.second < secondElem.second;
}