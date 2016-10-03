#include <stdio.h>
#include <iostream>
//#include "sthread.h"
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

/*void *trainMain(void *tsPtr, int dest){
	TrainStation *ts = (TrainStation *)tsPtr;
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
}*/


int main(int argc, char const *argv[]){
	
	//int ii = 1;
	TrainStation *ts = new TrainStation();

	/*TrainStation *ts = new TrainStation(1,1);
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

	ts->chooseRail(0);
    ts->getUnusedRails();


	return 0;
}
