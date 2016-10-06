#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>
#include <vector>
using namespace std;

const int NCONTAINRES = 5;
const int NO_CUST_CLOSING_TIME = -1;

class TrainStation{
 private:
	Lock lock[5];
	Cond wakeBarber;
	Cond nextCustomer;

	bool timeToClose;
	bool open;
    int totalCount;
	int arrivalCount;
	int cutCount;
	int fullCount;
	bool unusedRails[5];
	bool isChecking[5];
	bool isUnloading[5];
	int checkList[5];
	int unloadList[5];

	int waitingContainers[5];
	int sleepTime[5] = {2, 8, 6, 4, 10};
    vector<string> cities;
//	char* cities[5] = {"Stgo","Temuco","Antofagasta","Concepcion","Pto Montt"};

 public:
	TrainStation();
	~TrainStation() {};
	void loadContainer();
	void unloadContainer(int id);
	void travel(int id);
    int getTotalCount();
	void arriveContainer();
	void checkContainer(int id);
	void done(int id);
	int getCutCount();

// private:

};
#endif
