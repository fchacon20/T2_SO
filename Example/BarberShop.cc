/*
 * BarberShop.cc -- Barber shop for sleeping barber 
 * problem
 */
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "BarberShop.h"
#include "Lock.h"
#include "Cond.h"
#include "sthread.h"

void BarberShop::barberDay()
{
  // BarberDay is not an atomic action.
  // No lock. Only touch object's state 
  // by calling methods that lock.
  int cust;
  printf("Opening for the day\n");
  openStore();
  while(1){
    cust = waitForCustomer();
    if(cust == NO_CUST_CLOSING_TIME){
      printf("Closing for the day\n");
      printFinalStats();
      return;
    }
    printf("Cut hair %d\n", cust);
    sthread_sleep(1, 0); // Simulate time to cut
    doneCutting();
  }
}

void BarberShop::openStore()
{
  lock.Acquire();
  open = true;
  lock.Release();
  return;
}

int BarberShop::waitForCustomer()
{
  int custId;
  lock.Acquire();
  while(emptyAndOpen()){
    wakeBarber.Wait(&lock);
  }
  if(timeToClose){
    open = false; // Stop new arrivals
  }
  if(arrivalCount > cutCount){
    custId = cutCount;
  }
  else{
    custId = NO_CUST_CLOSING_TIME;
  }
  lock.Release();
  return custId;
}

void BarberShop::doneCutting()
{
  lock.Acquire();
  cutCount++; 
  nextCustomer.Broadcast(&lock);
  lock.Release();
  return;
}

void BarberShop::printFinalStats()
{
  lock.Acquire();
  printf("Stats: arrived=%d cut=%d full=%d\n",
         arrivalCount, cutCount, fullCount);
  assert(arrivalCount == cutCount); 
  lock.Release();
}

bool BarberShop::getHairCut()
{
  int myNumber;
  bool ret;
  lock.Acquire();
  if(!open || waitingRoomFull()){
    ret = false;
  }
  else{
    // "Take a number" to ensure FIFO service
    myNumber = ++arrivalCount;
    wakeBarber.Signal(&lock);
    while(stillNeedHaircut(myNumber)){
      nextCustomer.Wait(&lock);
    }
    ret = true;
  }
  lock.Release();
  return ret;
}

void BarberShop::clockRingsClosingTime()
{
  lock.Acquire();
  timeToClose = true;
  wakeBarber.Signal(&lock);
  lock.Release();
}

// Internal functions for checking status.
//  Always called with lock already held.
bool BarberShop::emptyAndOpen()
{
  if((timeToClose || (arrivalCount > cutCount))){
    return false;
  }
  else{
    return true;
  }
}

bool BarberShop::stillNeedHaircut(int custId)
{
  // Ensure FIFO order by letting customers
  // leave in order they arrive
  if(custId > cutCount){
    return true;
  }
  else{
    return false;
  }
}

bool BarberShop::waitingRoomFull()
{
  // +1 b/c barber chair
  if(arrivalCount - cutCount == NCHAIRS + 1){
    return true;
  }
  else{
    return false;
  }
}

// Routine constructor
BarberShop::BarberShop()
{
  open = false;
  timeToClose = false;
  arrivalCount = 0;
  cutCount = 0;
  fullCount = 0;
}

