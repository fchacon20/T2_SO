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

	int currentDestination;
	TrainStation *ts = (TrainStation *)tsPtr;

	currentDestination = ts->sendTrain();

	sthread_sleep(ts->sleepTime[currentDestination], 0);

	ts->trainDone(); //actualizar trenes activos, rieles usados, etc.

	return NULL;
}

void *containerMain(void *tsPtr){

	TrainStation *ts = (TrainStation *)tsPtr;
	int tryAgain = 1;
	while (tryAgain){
		tryAgain = ts->chooseRail();
	}

	//ts->sendTrain();
	//En este punto hay que indicarle al tren que parta, npi como hacerlo

	ts->unloadContainer();
	sthread_sleep(11, 0);
	ts->checkContainer();
	sthread_sleep(7, 0);

	//se hace algo mas??

	return NULL;

/*
	se asigna a un riel
	se envia en un tren
	- viaje -
	se baja del tren
	se chequea el container
	se descarga el container
	o primero se descarga y luego se chequea?
*/
}

int main(int argc, char const *argv[]){
	
	TrainStation *ts = new TrainStation();

	//Crear los threads de trenes,containers.


	//ts->chooseRail(0);
    	ts->getUnusedRails();


	return 0;
}
