#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
//#include "sthread.h"
#include <iostream>
#include <string>
using namespace std;

int TrainStation::chooseRail(){//Elige el riel por el cual enviar el proximo container
	int i;
	bool success = false;
	lock.Acquire();
	for (i = 0; i < 5; i++){
		if (unusedRails[i] && sentTrains[i] < 5){
			unusedRails[i] = false;
			nextDestination = i;
			success = true;
		}
	}
	lock.Release();
	if (success){
		return 0;
	}
	else{
		return 1;
	}
}

int TrainStation::sendTrain(){
	lock.Acquire();
	if (activeTrains < 5 && stationContainers > 0){
		//createTrain(nextDestination);
		activeTrains++;
		sentTrains[nextDestination]++;
		stationContainers--;
	}
	lock.Release();
	return nextDestination;
}

void TrainStation::trainDone(){
	return;
}

void TrainStation::checkContainer(){
	return;
}

void TrainStation::unloadContainer(){
	return;
}

bool TrainStation::checkCompletion(){
	//Verificar que todo este hecho
	return true;
}

void TrainStation::getUnusedRails() {
    for (int i = 0; i < 5; ++i) {
        cout << unusedRails[i] << endl;
    }
}

/*
TrainStation::TrainStation(){

	stationContainers = 25;
	activeTrains = 0;
	for(int i = 0; i < 5; i++) {
		sentTrains[i] = 0;
		unusedRails[i] = true;
	}
}
*/

TrainStation::TrainStation(){
	
	stationContainers = 25;
	activeTrains = 0;
	
}
