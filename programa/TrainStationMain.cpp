#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "TrainStation.h"

using namespace std;

#define NTRAINS 	5
#define NRAILS	 	5
#define NCONTAINERS	25
#define TSTGO 		2
#define TTMCO 		8
#define TANTOFA 	6
#define TCONCE 		4
#define TPTOMONTT 	10

void *trainMain(void *tsPtr, int dest){
	TrainStation *ts = (TrainStation *)bsPtr;
	while(1){
		ts->getOut();
		switch(dest){
			case(1):
				sthread_sleep(TSTGO,0);
				break;
			case(2):
				sthread_sleep(TTMCO,0);
				break;
			case(3):
				sthread_sleep(TANTOFA,0);
				break;
			case(4):
				sthread_sleep(TCONCE,0);
				break;
			case(5):
				sthread_sleep(TPTOMONTT,0);
				break;
			default:
				cout << "Something is wrong" << endl;
				break;
		}
		
	}
	return NULL;
}


int main(int argc, char const *argv[]){
	
	int ii = 1;
	Train *ts = new TrainStation();
	Train trains[NTRAINS];
	Rail rails[NRAILS];
	//sthread_t trains[NTRAINS];

	//Creacion de trenes y rieles, 5 de ellos, 1 por cada riel
	for(ii = 0; ii < NTRAINS; ii++)
		trains[ii] = new Train(ii+1, ii+1);
	
	for(ii = 0; ii < NRAILS; ii++)
		rails[ii] = new Rail(ii+1);

	//Creacion y asignacion de containers
	int i = -1;
	for(ii = 0; ii < NCONTAINERS; ii++){
		if (ii%5 == 0)
			i++;
		rails[i].containers.push_back(new Container(ii+1));

	//Primera asignacion de container a tren
	for (int i = 0; i < NTRAINS; í++){
		trains[i].container = &rails[i].containers.back();
		rails[i].containers.pop_back();
	}
	

/*	TrainStation *ts = new TrainStation(1,1);
	switch (ts->dest){
		case(1):
			cout << "stgo" << endl;
			break;
		case(2):
			cout << "stgo" << endl;
			break;
		default:
			cout << "Winter is coming" << endl;
	}*/

	return 0;
}
