#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

TrainStation::TrainStation(int dest, int iid){
	dest = dest;
	id = iid;
}
