#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class TrainStation{
	private:
		Lock lock;
		Cond nextContainer;

	public:
		TrainStation();
		~TrainStation();
	
};
#endif
