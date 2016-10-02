#include "Train.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

Train::Train(int iid, int dest){
	dst = dest;
	id = iid;
}