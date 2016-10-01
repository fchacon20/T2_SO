all: main

main: main sthread.o Lock.o Train Cond.o
	g++ -pthread main.o Train.o sthread.o Lock.o Cond.o -o main

Train:  Train.h Train.cpp
	g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS Train.cpp -c -o Train.o
Cond.o: Lock.o Cond.cc Cond.h
	g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Cond.cc -c -o Cond.o
Lock.o: sthread.o Lock.cc Lock.h
	 g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Lock.cc -c -o Lock.o
sthread.o: sthread.c sthread.h
	gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS sthread.c -c -o sthread.o
main: main.cpp
		g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS main.cpp -c -o main.o
clean:
	rm -rf *.o main
