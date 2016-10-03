#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
//#include "sthread.h"
#include <iostream>
#include <string>
using namespace std;

void TrainStation::chooseRail(int dest){
	lock.Acquire();
	if (unusedRails[dest]){
		unusedRails[dest] = false;
		nextDestination = dest;
	}
	lock.Release();
}

void TrainStation::deployTrain(){
	lock.Acquire();
	if (activeTrains < 5 && stationContainers > 0){
		//createTrain(nextDestination);
		activeTrains++;
		sentTrains[nextDestination]++;
		stationContainers--;
	}
	lock.Release();
}

bool TrainStation::checkCompletion(){
	//Verificar que todo este hecho
}

void TrainStation::getUnusedRails() {
    for (int i = 0; i < 5; ++i) {
        cout << unusedRails[i] << endl;
    }
}

TrainStation::TrainStation(){

	stationContainers = 25;
	activeTrains = 0;
	for(int i = 0; i < 5; i++) {
		sentTrains[i] = 0;
		unusedRails[i] = true;
	}
}