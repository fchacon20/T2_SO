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

void TrainStation::barberDay()
{
  // BarberDay is not an atomic action.
  // No lock. Only touch object's state 
  // by calling methods that lock.
  int cust;
  int idRail = 0;
  printf("Opening for the day\n");
  openStore();
  while(1){
    cust = waitForCustomer();
    /*if(cust == NO_CUST_CLOSING_TIME){
      printf("Closing for the day\n");
      printFinalStats();
      return;
    }*/
    if (cust%5 == 0)
    	idRail = 0;
    idRail++;
    printf("Container asignado a riel %d\n", idRail);
    sthread_sleep(sleepTime[idRail-1], 0); // Simulate time to cut
    cout << "Tren llega a destino " << idRail << endl;
    doneCutting();
  }
}

void TrainStation::openStore()
{
  lock.Acquire();
  open = true;
  lock.Release();
  return;
}

int TrainStation::waitForCustomer()
{
  int custId;
  lock.Acquire();
  while(emptyAndOpen()){
    wakeBarber.Wait(&lock);
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
  lock.Release();
  return custId;
}

void TrainStation::doneCutting()
{
  lock.Acquire();
  cutCount++; 
  nextCustomer.Broadcast(&lock);
  lock.Release();
  return;
}

void TrainStation::printFinalStats()
{
  lock.Acquire();
  printf("Stats: arrived=%d cut=%d full=%d\n",
         arrivalCount, cutCount, fullCount);
  assert(arrivalCount == cutCount); 
  lock.Release();
}

bool TrainStation::getHairCut()
{
  int myNumber;
  bool ret;
  lock.Acquire();
  if(!open || waitingRoomFull()){
    ret = false;
  }
  else{
    // "Take a number" to ensure FIFO service
    myNumber = ++arrivalCount;
    wakeBarber.Signal(&lock);
    while(stillNeedHaircut(myNumber)){
      nextCustomer.Wait(&lock);
    }
    ret = true;
  }
  lock.Release();
  return ret;
}

void TrainStation::clockRingsClosingTime()
{
  lock.Acquire();
  timeToClose = true;
  wakeBarber.Signal(&lock);
  lock.Release();
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
	open = false;
	timeToClose = false;
	arrivalCount = 0;
	cutCount = 0;
	fullCount = 0;
	
}
