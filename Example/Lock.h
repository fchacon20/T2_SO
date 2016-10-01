/*
 * Lock.h -- simple mutual exclusion lock based on posix pthreads lock
 */
#ifndef _LOCK_H_
#define  _LOCK_H_
#include <pthread.h>

class Lock{
  friend class Cond;
 private:
  pthread_mutex_t lock;
 public: 
  Lock();
  ~Lock();
  void Acquire();
  void Release();
 protected:
  pthread_mutex_t *getRawLock(); // Cond needs this
};
#endif
