#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class TrainStation{
	private:
		Lock lock;
		Cond nextContainer;
		int stationContainers;
		int sentTrains [5] = {0, 0, 0, 0, 0};  //indice indica el destino;
		bool unusedRails [5] = {true, true, true, true, true}; //indice indica el destino;
		bool workIsDone;

	public:
		int dest; //stgo: 0, tmco: 1, antofa: 2, conce: 3, ptomontt: 4
		int id; //del 1 al 15, o del 1 al 25?
		int nextDestination;
		int activeTrains;
		int sleepTime [5] = {2, 8, 6, 4, 10};
		int chooseRail();
		int sendTrain();
		void trainDone();
		void unloadContainer();
		void checkContainer();
		void getUnusedRails();
		bool checkCompletion();
		TrainStation();
		~TrainStation();
	
};
#endif
