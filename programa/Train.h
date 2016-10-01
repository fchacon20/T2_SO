#ifndef _TRAIN_H_
#define _TRAIN_H_
#include "Lock.h"
#include "Cond.h"
#include <string>

class Train{
	private:
		Lock lock;
		Cond nextContainer;

		string dst;

	public:
		Train(string dst);
		~Train();
		void goOut();
	
};
#endif