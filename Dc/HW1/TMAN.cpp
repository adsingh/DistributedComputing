#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Node.h"
#include "DRTopology.h"
#include "BTTopology.h"

using namespace std;

int radius;

int main(int argc, char* argv[]){

	int N;
	int k;
	char topology;
	N = atoi(argv[1]);

	k = atoi(argv[2]);
	topology = argv[3][0];
	char* R;
	char* r;
	vector<int> radii;
	//cout << "N = " << N << " k = " << k << endl;

	DRTopology* T;
	BTTopology* BT;

	switch(topology){

		case 'D' :

			cout << "D\n";
			R = argv[5];
			r = strtok(R, ",");
			while(r != NULL){
				radii.push_back(atoi(r));
				r = strtok(NULL, ",");
			}
			//radius = argv[4][0]-48;
			//cout << "radius = " << radius << endl;
			T = new DRTopology(N,k,radii);
			T->becomeOptimal();
			T->createDataSet();
			T->plot();
			/*for(int i = 0 ; i < k ; i++){
				cout << T->topo[13]->nbIds[i] << ' ';
			}
			cout << endl;*/
			break;

		case 'B' :

			cout << "B\n";
			BT = new BTTopology(N,k);
			BT->becomeOptimal();
			BT->createDataSet();
			for(int i = 0 ; i < k ; i++){
				cout << BT->topo[3]->nbIds[i] << ' ';
			}
			cout << endl;
			BT->plot();
			break;

		case 'C' :

			cout << "C\n";
			break;

	}

	return 0;
}