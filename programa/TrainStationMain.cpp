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

void *railMain(void *bsPtr){
    TrainStation *bs = (TrainStation *)bsPtr;
    while (bs->getCutCount() != NCONTAINERS);
    cout << "Se movieron " << bs->getCutCount() << " contenedores" << endl;
    return NULL;
}

void *containerMain(void *bsPtr){
  TrainStation *bs = (TrainStation *)bsPtr;
  while(1){
    bs->loadContainer();
  }
  return NULL;
}

int main(int argc, char **argv){
    TrainStation *bs = new TrainStation();
    sthread_t rail;
    sthread_t containers[NCONTAINERS];
    sthread_create_p(&rail, railMain, bs);

    for(int i = 0; i < NCONTAINERS; i++){
        sthread_create_p(&containers[i], containerMain, bs);
    }

    sthread_join(rail);
    

}
