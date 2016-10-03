#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class TrainStation{
private:
	Lock lock;
	Cond nextContainer;
	int nextDestination;
	int stationContainers;
	int activeTrains;
	int sentTrains [5];  //indice indica el destino;
	bool unusedRails [5]; //indice indica el destino;
	bool workIsDone;

public:
	int dest; //stgo: 0, tmco: 1, antofa: 2, conce: 3, ptomontt: 4
	int id; //del 1 al 15, o del 1 al 25?
    void chooseRail(int dest);
    void deployTrain();
    bool checkCompletion();
    void getUnusedRails();
	TrainStation();
	~TrainStation();

};
#endif