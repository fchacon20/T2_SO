#ifndef _TRAINSTATION_H_
#define _TRAINSTATION_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class TrainStation{
	private:
		Lock lock;
		Cond nextContainer;

		int dest; //stgo: 1, tmco: 2, antofa: 3, conce: 4, ptomontt: 10
		int id; //del 1 al 15, o del 1 al 25?

	public:
		TrainStation(int dest, int iid);
		~TrainStation();
	
};
#endif