#include <stdio.h>
#include <iostream>
#include "sthread.h"
#include "Train.h"
#include <vector>

using namespace std;

#define NTRAINS 	5
#define TSTGO 		2
#define TTMCO 		8
#define TANTOFA 	6
#define TCONCE 		4
#define TPTOMONTT 	10

int main(int argc, char const *argv[]){

	vector<Train> trains;
	
	trains.push_back(Train stgo("stgo"));
	
	for (vector<Train>::iterator i = trains.begin(); i != trains.end(); ++i)
	{
		cout << *i.dst << endl;
	}

	return 0;
}