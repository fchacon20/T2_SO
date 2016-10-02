#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class Container{
	private:
		Lock lock;
		Cond nextContainer;

		int id; //del 1 al 15, o del 1 al 25?

	public:
		Container(int iid);
		~Container();
	
};
#endif