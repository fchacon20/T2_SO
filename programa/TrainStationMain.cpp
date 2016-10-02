#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "TrainStation.h"

using namespace std;

#define NTRAINS 	5
#define TSTGO 		2
#define TTMCO 		8
#define TANTOFA 	6
#define TCONCE 		4
#define TPTOMONTT 	10

int main(int argc, char const *argv[]){
	
	TrainStation *ts = new TrainStation(1,1);
	switch (ts->dest){
		case(1):
			cout << "stgo" << endl;
			break;
		case(2):
			cout << "stgo" << endl;
			break;
		default:
			cout << "Winter is coming" << endl;
	}
	return 0;
}
