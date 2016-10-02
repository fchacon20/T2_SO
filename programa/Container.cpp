#include "Container.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"
#include <string>

Container::Container(int iid){
	id = iid;
}