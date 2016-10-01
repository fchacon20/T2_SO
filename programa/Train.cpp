#include "Train.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

void Train::Train(string dest){
	dst = dest;
}

void Train::goOut(){

}