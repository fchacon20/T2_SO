all: TrainSMain

TrainSMain: TrainStationMain sthread.o Lock.o TrainStation Cond.o
	g++ -pthread TrainStationMain.o TrainStation.o sthread.o Lock.o Cond.o -o TrainStationMain

TrainStation:  TrainStation.h TrainStation.cpp
	g++ -g -std=c++11 -Wall -Werror -D_POSIX_THREAD_SEMANTICS TrainStation.cpp -c -o TrainStation.o
Cond.o: Lock.o Cond.cc Cond.h
	g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Cond.cc -c -o Cond.o
Lock.o: sthread.o Lock.cc Lock.h
	 g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Lock.cc -c -o Lock.o
sthread.o: sthread.c sthread.h
	gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS sthread.c -c -o sthread.o
TrainStationMain: TrainStationMain.cpp
		g++ -g -std=c++11 -Wall -Werror -D_POSIX_THREAD_SEMANTICS TrainStationMain.cpp -c -o TrainStationMain.o
clean:
	rm -rf *.o TrainStationMain
