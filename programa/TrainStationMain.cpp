#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "TrainStation.h"

using namespace std;

#define NCONTAINERS	15

void *stationMain(void *tsPtr){
    TrainStation *ts = (TrainStation *)tsPtr;
    while (ts->getCutCount() != NCONTAINERS);
    cout << "Se movieron " << ts->getCutCount() << " contenedores" << endl;
    return NULL;
}

void *containerMain(void *tsPtr){
  TrainStation *ts = (TrainStation *)tsPtr;
  while(ts->getTotalCount() != NCONTAINERS){
    ts->loadContainer();
  }
  return NULL;
}

int main(int argc, char **argv){
    TrainStation *ts = new TrainStation();
    sthread_t station;
    sthread_t containers[NCONTAINERS];
    sthread_create_p(&station, stationMain, ts);

    for(int i = 0; i < NCONTAINERS; i++){
        sthread_create_p(&containers[i], containerMain, ts);
    }

    sthread_join(station);
    

}
