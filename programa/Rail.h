#ifndef _RAIL_H_
#define _RAIL_H_
#include "Lock.h"
#include "Cond.h"
#include <string>
#include <vector>

class Rail{
	private:
		Lock lock;
		Cond nextRail;

		int id; //del 1 al 5 por el destino
		vector<Container> containers;

	public:
		Rail(int iid);
		~Rail();
	
};
#endif