#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <iostream>
#include <string>

#include <stdio.h>
using namespace std;

void TrainStation::loadContainer() {

    int id;
    arrivalCount = ((arrivalCount+1)%5);
    lock[arrivalCount].Acquire();
    totalCount++;
    printf("Container esperando en riel %d\n", arrivalCount+1);
    waitingContainers[arrivalCount] += 1;
    id = arrivalCount;
    lock[arrivalCount].Release();

    travel(id);
	unloadContainer(id);
	checkContainer(id);
    done(id);
    return;
}

int TrainStation::getCutCount() {
    return cutCount;
}

int TrainStation::getTotalCount() {
    return totalCount;
}

void TrainStation::arriveContainer(){
    
    return;
}

void TrainStation::travel(int id){

	lock[id].Acquire();
    while(!unusedRails[id]);
    waitingContainers[id]--;
    unusedRails[id] = false;
    printf("> Container subido a tren %d con rumbo a %s, demorara %d segundos\n", id+1,  cities[id].c_str(), sleepTime[id]);
    sthread_sleep(sleepTime[id], 0);

    lock[id].Release();
    return;
}

void TrainStation::unloadContainer(int id){
    lock[id].Acquire();
    unusedRails[id] = true;
    while (isChecking[id]);
    isUnloading[id] = true;
    unloadList[id] += 1;
    printf(">> Descargando container en %s\n", cities[id].c_str());
    sthread_sleep(11, 0);
    printf(">> Descarga de container en %s lista\n", cities[id].c_str());
    isUnloading[id] = false;

    lock[id].Release();
    return;
}

void TrainStation::checkContainer(int id){
    lock[id].Acquire();
	while(isUnloading[id]);
	isChecking[id] = true;
	checkList[id] += 1;
    printf(">>> Checkeando container en %s\n",  cities[id].c_str());
	sthread_sleep(7, 0);
	printf(">>> Checkeo de container en %s listo\n", cities[id].c_str());
	isChecking[id] = false;
	lock[id].Release();
    return;
}

void TrainStation::done(int id){
    printf(">>>> Fin del container en %s\n",  cities[id].c_str());
    cutCount++;
    return;
}

TrainStation::TrainStation(){

	open = true;
	timeToClose = false;
	arrivalCount = 1;
	cutCount = 0;
	fullCount = 0;

    for(int i = 0; i < 5; i++){
        unusedRails[i] = true;
        isChecking[i] = false;
        isUnloading[i] = false;
        checkList[i] = 0;
        unloadList[i] = 0;
        waitingContainers[i] = 0;
    }

    totalCount = 0;

    cities.push_back("Stgo");
    cities.push_back("Temuco");
    cities.push_back("Antofagasta");
    cities.push_back("Concepcion");
    cities.push_back("Pto Montt");

}
