#include "DRTopology.h"

DRTopology::DRTopology(int n, int k, vector<int> radii)
{
	cout << "Hi\n";
	numberOfNodes = n;
	this->radii = radii;
	currentRadius = radii[0];
	targetRadius = radii[0];
	noOfNbs = k;
	float angle = 0;
	float inr = 2 * M_PI / numberOfNodes;
	for(int i = 0 ; i < numberOfNodes; i++){
		//cout << "angle = " << angle << endl;
		Node* next =  new Node(angle);
		//srand(time(NULL)-1);
		initNeighbours(next, i);
		topo.push_back(next);
		angle += inr;
	}
}

void DRTopology::initNeighbours(Node* next, int myID){

	for(int i = 0 ; i < noOfNbs ; i++){
		int id = (int)(((((double)std::rand()) / RAND_MAX) * numberOfNodes));
		//cout << "id = " << id << endl;
		if(id == myID){
			i--;
			continue;
		}
		next->nbIds.push_back(id);
	}
}

//void printNeighbours()
void DRTopology::becomeOptimal(){

	int count = 1;
	for(int i = 0; i < 50 ; i++){

		if(i > 0 && i % 5 == 0 && count < radii.size()){
			targetRadius = radii[count];
			count++;
		}
		if(i>0 && i %3 == 0 && currentRadius < targetRadius)
			currentRadius++;
		cout << "radius = " << currentRadius << " target = " << targetRadius << endl;
		Node* current;
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
			}while(currentNbId == n);
			Node* neighbour =  topo[currentNbId];

			updateNbIDs(current, neighbour);
			for(int i = 0; i < current->nbIds.size() ; i++){
				//cout << current->nbIds[i] << ' ';
			}
			//cout << endl;

		}
	}
}

void DRTopology::updateNbIDs(Node* current, Node* neighbour){

	/*cout << "before: current size = " << current->nbIds.size() << " neighbour size = " << neighbour->nbIds.size() << "\n";
	for(int i = 0; i < current->nbIds.size() ; i++){
		cout << current->nbIds[i] << ' ';
	}
	cout << endl;
	for(int i = 0; i < neighbour->nbIds.size() ; i++){
		cout << neighbour->nbIds[i] << ' ';
	}
	cout << endl;*/
	vector<pair<int, float> > v1, v2;
	current->nbIds.insert(current->nbIds.end(), neighbour->nbIds.begin(), neighbour->nbIds.end());
	sort(current->nbIds.begin(), current->nbIds.end());
	float dist;
	vector<int>::iterator it;
	int prev = -1;
	for(it = current->nbIds.begin(); it != current->nbIds.end(); it++){
		if(it != current->nbIds.begin() && *it == prev)
			continue;
		dist = sqrt(pow((topo[*it]->location.first - current->location.first)*currentRadius , 2) + pow((topo[*it]->location.second - current->location.second)*currentRadius,2));
		v1.push_back(make_pair(*it, dist));
		dist = sqrt(pow((topo[*it]->location.first - neighbour->location.first)*currentRadius,2) + pow((topo[*it]->location.second - neighbour->location.second)*currentRadius,2));
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

void DRTopology::createDataSet(){

	//cout << "inside dataset\n";
	ofstream dataFile("data.txt");
	for(int i = topo.size() -1 ; i > -1 ; i--){
		int nb;
		for(int j = 0 ; j < noOfNbs; j++){
			dataFile << topo[i]->location.first*currentRadius << ' ' << topo[i]->location.second*currentRadius << endl;
			nb = topo[i]->nbIds[j];
			dataFile << topo[nb]->location.first*currentRadius << ' ' << topo[nb]->location.second*currentRadius << endl << endl;
		}
	}
	dataFile.close();
}

void DRTopology::plot(){
	//cout << "MAKING SYSCALL\n";
	system("gnuplot mine");

}

bool DRTopology::pairCompare(const pair<int, float>& firstElem, const pair<int, float>& secondElem){
	return firstElem.second < secondElem.second;
}