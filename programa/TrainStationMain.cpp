#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "TrainStation.h"

using namespace std;

#define NCONTAINERS	5

void *railMain(void *bsPtr){
    TrainStation *bs = (TrainStation *)bsPtr;
    while (bs->getCutCount() != NCONTAINERS);
    cout << "Se movieron " << bs->getCutCount() << " contenedores" << endl;
    return NULL;
}

void *containerMain(void *bsPtr){
  TrainStation *bs = (TrainStation *)bsPtr;
  while(bs->getTotalCount() != NCONTAINERS){
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
