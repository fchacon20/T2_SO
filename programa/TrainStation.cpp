#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

bool TrainStation::getOut(){
	bool ret = true;
	lock.Acquire();
	lock.Release();
	return ret;
}

TrainStation::TrainStation(int dest, int iid){
	dest = dest;
	id = iid;
}

bool TrainStation::AssignRail(){
	
}