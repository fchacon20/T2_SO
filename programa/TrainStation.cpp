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

bool TrainStation::AssignRail(){
	
}