#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "TrainStation.h"

using namespace std;

#define NTRAINS 	5
#define NRAILS	 	5
#define NCONTAINERS	15
#define TSTGO 		2
#define TTMCO 		8
#define TANTOFA 	6
#define TCONCE 		4
#define TPTOMONTT 	10
#define SIMTIME 	10

/*void *trainMain(void *tsPtr, int dest){

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

	ts->getUnusedRails();
	//ts->sendTrain();
	//En este punto hay que indicarle al tren que parta, npi como hacerlo
*/
	/*ts->unloadContainer();
	sthread_sleep(11, 0);
	ts->checkContainer();
	sthread_sleep(7, 0);
*/
	//se hace algo mas??

//	return NULL;

/*
	se asigna a un riel
	se envia en un tren
	- viaje -
	se baja del tren
	se chequea el container
	se descarga el container
	o primero se descarga y luego se chequea?
*/
/*}

int main(int argc, char const *argv[]){
	
	TrainStation *ts = new TrainStation();

	//Crear los threads de trenes,containers.

	//ts->chooseRail(0);

    sthread_t container[2];
    sthread_create_p(&container[0], containerMain, ts);
	sthread_create_p(&container[1], containerMain, ts);

	sthread_join(container[1]);

	return 0;
}*/

void *railMain(void *bsPtr)
{
  TrainStation *bs = (TrainStation *)bsPtr;
    //bs->unloadContainer();
    //sthread_sleep(1,0);
    while (bs->getCutCount() != NCONTAINERS){

    }
  return NULL;
}

void *containerMain(void *bsPtr)
{
  TrainStation *bs = (TrainStation *)bsPtr;
  while(1){
    bs->loadContainer();
    //sthread_exit(1);
    //sthread_sleep(1, 0);
  }
  return NULL;
}

/*void *clockMain(void *bsPtr)
{
  TrainStation *bs = (TrainStation *)bsPtr;
  sthread_sleep(SIMTIME, 0);
  printf("CLOCK: Closing time\n");
  bs->clockRingsClosingTime();
  return NULL;
}*/


int main(int argc, char **argv)
{
  int ii;
  TrainStation *bs = new TrainStation();
  sthread_t rails[NRAILS];
  sthread_t containers[NCONTAINERS];
  //sthread_t clock;

    for (int j = 0; j < NRAILS; ++j) {
        sthread_create_p(&rails[j], railMain, bs);
    }

  //sthread_create_p(&clock, clockMain, bs);

  for(ii = 0; ii < NCONTAINERS; ii++){
    sthread_create_p(&containers[ii], containerMain, bs);
  }

    for (int i = 0; i < NRAILS; ++i) {
        sthread_join(rails[i]);
    }

}
