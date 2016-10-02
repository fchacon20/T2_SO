#include "TrainStation.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

void TrainStation::TrainStation(int dest, int iid){
	dst = dest;
	id = iid;
}
