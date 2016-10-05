#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

void TrainStation::loadContainer() {

    int id;
    arrivalCount = ((arrivalCount+1)%5);
    lock[arrivalCount].Acquire();
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

void TrainStation::arriveContainer(){
    
    return;
}

void TrainStation::travel(int id){

	lock[id].Acquire();
    while(!unusedRails[id]);
    waitingContainers[id]--;
    unusedRails[id] = false;
    printf("> Container subido a tren %d, demorara %d segundos\n", id+1, sleepTime[id]);
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
    printf(">> Descargando container en %s\n", cities[id+1]);
    sthread_sleep(11, 0);
    printf(">> Descarga de container en %d lista",id+1);
    isUnloading[id] = false;

    lock[id].Release();
    return;
}

void TrainStation::checkContainer(int id){
    lock[id].Acquire();
	while(isUnloading[id]);
	isChecking[id] = true;
	checkList[id] += 1;
    printf(">>> Checkeando container en %d\n", id+1);
	sthread_sleep(7, 0);
	printf(">>> Checkeo de container en %d listo\n",id+1);
	isChecking[id] = false;
	lock[id].Release();
    return;
}

void TrainStation::done(int id){
    printf(">>>> Fin del container en %d\n", id+1);
    //unusedRails[arrivalCount] = true;
    cutCount++;
    return;
}

TrainStation::TrainStation(){
	
	//stationContainers = 25;
	//activeTrains = 0;
	open = true;
	timeToClose = false;
	arrivalCount = 1;
	cutCount = 0;
	fullCount = 0;
	
}
