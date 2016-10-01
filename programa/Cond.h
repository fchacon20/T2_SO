/*
 * Cond.h -- simple condition variable based on pthreads cv
 */
#ifndef _COND_H_
#define _COND_H_
#include <pthread.h>
#include "Lock.h"

class Cond{
 private:
  pthread_cond_t cond;
 public:
  Cond();
  ~Cond();
  void Wait(Lock *lock);
  void Signal(Lock *lock);
  void Broadcast(Lock *lock);
};
#endif
