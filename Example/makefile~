all: BarberMain

BarberMain: BarberShopMain sthread.o Lock.o BarberShop Cond.o
	g++ -lpthread BarberShopMain.o BarberShop.o sthread.o Lock.o Cond.o -o BarberMain

BarberShop:  BarberShop.h BarberShop.cc
	g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS BarberShop.cc -c -o BarberShop.o
Cond.o: Lock.o Cond.cc Cond.h
	g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Cond.cc -c -o Cond.o
Lock.o: sthread.o Lock.cc Lock.h
	 g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS  Lock.cc -c -o Lock.o
sthread.o: sthread.c sthread.h
	gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS sthread.c -c -o sthread.o
BarberShopMain: BarberShopMain.cc
		g++ -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS BarberShopMain.cc -c -o BarberShopMain.o
clean:
	rm -rf *.o BarberMain
