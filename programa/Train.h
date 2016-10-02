#ifndef _TRAIN_H_
#define _TRAIN_H_
#include "Lock.h"
#include "Cond.h"
#include "Container.h"
#include <string>

class Train{
	private:
		Lock lock;
		Cond nextContainer;

		Container *container;
		int dst; //stgo: 1, tmco: 2, antofa: 3, conce: 4, ptomontt: 10
		int id; //del 1 al 15, o del 1 al 25?

	public:
		Train(int iid, int dest);
		~Train();
	
};
#endif