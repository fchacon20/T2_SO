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

/*
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


TrainStation::TrainStation(){

	stationContainers = 25;
	activeTrains = 0;
	for(int i = 0; i < 5; i++) {
		sentTrains[i] = 0;
		unusedRails[i] = true;
	}
}
*/

void TrainStation::loadContainer() {

    arrivalCount = (++arrivalCount)%5;
    lock[arrivalCount].Acquire();
    cout << "Container esperando en riel " << arrivalCount + 1 << endl;
    waitingContainers[arrivalCount] = 1;
    lock[arrivalCount].Release();
    travel();
    arriveContainer();
    unloadContainer();
    checkContainer();
    done();
    return;
}

int TrainStation::getCutCount() {
    return cutCount;
}
void TrainStation::arriveContainer(){
    unusedRails[arrivalCount] = true;
    return;
}
/*int TrainStation::sendTrain(){
    lock.Acquire();
    if (activeTrains < 5 && stationContainers > 0){
        //createTrain(nextDestination);
        activeTrains++;
        sentTrains[nextDestination]++;
        stationContainers--;
    }
    lock.Release();
    return nextDestination;
}*/

void TrainStation::travel(){
    lock[arrivalCount].Acquire();
    if (unusedRails[arrivalCount]) {
        unusedRails[arrivalCount] = false;
        cout << "Container subido a tren " << arrivalCount + 1 << ", demorara " << sleepTime[arrivalCount] << " segundos" << endl;
        sthread_sleep(sleepTime[arrivalCount], 0);
    }
    lock[arrivalCount].Release();
    return;
}

void TrainStation::unloadContainer(){
    lock[arrivalCount].Acquire();
    cout << "Descargando container en " << arrivalCount << endl;
    sthread_sleep(11, 0);
    lock[arrivalCount].Release();
    return;
}

void TrainStation::checkContainer(){
    lock[arrivalCount].Acquire();
    cout << "Checkeando container en " << arrivalCount << endl;
    sthread_sleep(7, 0);
    lock[arrivalCount].Release();
    return;
}

void TrainStation::done(){
    cutCount++;
    return;
}
void TrainStation::barberDay()
{
  int cust;
  int idRail = 0;
  //  while(arrivalCount < 15) {
//        cust = waitForCustomer();
//        cout << "Container " << cust << " cargado a tren" << endl;
//    }
  // openStore();
  while(1){
    cust = waitForCustomer();
    if(cust == 15){
      printf("Closing for the day\n");
      //printFinalStats();
      return;
    }
    if (cust%5 == 0)
    	idRail = 0;
    idRail++;
      //loadContainer(cust);
    /*printf("Container asignado a riel %d\n", idRail);
    sthread_sleep(sleepTime[idRail-1], 0); // Simulate time to cut
    cout << "Tren llega a destino " << idRail << endl;
    doneCutting();*/
  }
}

void TrainStation::openStore()
{
  lock[arrivalCount].Acquire();
  open = true;
  lock[arrivalCount].Release();
  return;
}

int TrainStation::waitForCustomer()
{
  int custId;
  lock[arrivalCount].Acquire();
  while(emptyAndOpen()){
    wakeBarber.Wait(&lock[arrivalCount]);
  }
  //if(timeToClose){
    //open = false; // Stop new arrivals
  //}
  if(arrivalCount > cutCount){
    custId = cutCount;
  }
  else{
    custId = NO_CUST_CLOSING_TIME;
  }
  lock[arrivalCount].Release();
  return custId;
}

void TrainStation::doneCutting()
{
  lock[arrivalCount].Acquire();
  cutCount++; 
  nextCustomer.Broadcast(&lock[arrivalCount]);
  lock[arrivalCount].Release();
  return;
}

void TrainStation::printFinalStats()
{
  lock[arrivalCount].Acquire();
  printf("Stats: arrived=%d cut=%d full=%d\n",
         arrivalCount, cutCount, fullCount);
  assert(arrivalCount == cutCount); 
  lock[arrivalCount].Release();
}

bool TrainStation::getHairCut()
{
  int myNumber;
  bool ret;
  lock[arrivalCount].Acquire();
  if(!open || waitingRoomFull()){
    ret = false;
  }
  else{
    // "Take a number" to ensure FIFO service
    myNumber = ++arrivalCount;
    wakeBarber.Signal(&lock[arrivalCount]);
    while(stillNeedHaircut(myNumber)){
      nextCustomer.Wait(&lock[arrivalCount]);
    }
    ret = true;
  }
  lock[arrivalCount].Release();
  return ret;
}

void TrainStation::clockRingsClosingTime()
{
  lock[arrivalCount].Acquire();
  timeToClose = true;
  wakeBarber.Signal(&lock[arrivalCount]);
  lock[arrivalCount].Release();
}

// Internal functions for checking status.
//  Always called with lock already held.
bool TrainStation::emptyAndOpen()
{
  if((timeToClose || (arrivalCount > cutCount))){
    return false;
  }
  else{
    return true;
  }
}

bool TrainStation::stillNeedHaircut(int custId)
{
  // Ensure FIFO order by letting customers
  // leave in order they arrive
  if(custId > cutCount){
    return true;
  }
  else{
    return false;
  }
}

bool TrainStation::waitingRoomFull()
{
  // +1 b/c barber chair
  if(arrivalCount - cutCount == 5 + 1){ //cambiar por NCONTAINERS
    return true;
  }
  else{
    return false;
  }
}

TrainStation::TrainStation(){
	
	//stationContainers = 25;
	//activeTrains = 0;
	open = true;
	timeToClose = false;
	arrivalCount = 0;
	cutCount = 0;
	fullCount = 0;
	
}
