#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

const int NCONTAINRES = 5;
const int NO_CUST_CLOSING_TIME = -1;
/*
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
	
};*/
class TrainStation{
 private:
  Lock lock[5];
  Cond wakeBarber;
  Cond nextCustomer;

  bool timeToClose;
  bool open;
  int arrivalCount;
  int cutCount;
  int fullCount;
    bool unusedRails[5] = {true,true,true,true,true};
    int waitingContainers[5] = {0,0,0,0,0};
  int sleepTime [5] = {2, 8, 6, 4, 10};

 public:
  TrainStation();
  ~TrainStation() {};
  void barberDay(); // Main loop for barber thread
  bool getHairCut(); // Called by customer thread
  void clockRingsClosingTime(); // Called by clock thread
    void loadContainer();
    void unloadContainer();
    void travel();

 private:
  void openStore();
  int waitForCustomer();
  void doneCutting();
  void printFinalStats();

  bool emptyAndOpen();
  bool stillNeedHaircut(int custId);
  bool waitingRoomFull();
};
#endif
