#include <assert.h>
#include <pthread.h>
#include "Cond.h"
#include "Lock.h"

Cond::Cond()
{
  int err = pthread_cond_init(&cond, NULL);
  assert(!err);
}

Cond::~Cond()
{
  int err = pthread_cond_destroy(&cond);
  assert(!err);
}

void
Cond::Wait(Lock *lock)
{
  int err = pthread_cond_wait(&cond, lock->getRawLock());
  assert(!err);
}

void 
Cond::Signal(Lock *)
{
  int err = pthread_cond_signal(&cond);
  assert(!err);
}

void 
Cond::Broadcast(Lock *)
{
  int err = pthread_cond_broadcast(&cond);
  assert(!err);
}
