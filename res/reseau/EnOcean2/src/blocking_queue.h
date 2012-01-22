


#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <deque>
#include <vector>

using namespace std;


template <class value_type> class blocking_queue {

  deque<value_type *> data;

  unsigned int maxsize;

  /* Flag a thread to stop blocking on an empty queue. */
  bool qdone;

  /* Controls access to the queue's internal state. */
  pthread_mutex_t qlock;

  /* Signals threads waiting for the queue to wake up. */
  pthread_cond_t qcond;

public:

  /* maxsize == 0 means grow without bound. maxsize > 0 means that push
   * will block while the queue is full. */
  blocking_queue(unsigned int maxsize = 0);

  ~blocking_queue();

  /* Return 0 for success, ETIMEDOUT for a time-out, or -1 for other error. */
  int push(value_type *item);

  /* Return 0 for success, ETIMEDOUT for a time-out, EWOULDBLOCK if the queue is
   * no longer receiving data and would block indefinitely, or -1 for other
   * error.  timeout == NULL means block indefinitely, or until another thread
   * calls signal_done(). timeout == 0 means immediately return data if there is
   * any available, or otherwise immediately return EWOULDBLOCK. */
  int front(value_type *&item);

  /* Return 0 for success, or -1 if the queue is empty. */
  int pop();

};

template <class value_type>
blocking_queue<value_type>::blocking_queue(unsigned int maxsize) {
  this->maxsize = maxsize;
  this->qdone = false;
  pthread_mutex_init(&this->qlock, NULL);
  pthread_cond_init(&this->qcond, NULL);
}

template <class value_type>
blocking_queue<value_type>::~blocking_queue() {
  pthread_mutex_destroy(&this->qlock);
  pthread_cond_destroy(&this->qcond);
}

template <class value_type>
int blocking_queue<value_type>::push(value_type *item)
{
  int rv = 0;
  pthread_mutex_lock(&this->qlock);
  if(this->maxsize > 0) {
    while(this->data.size() == this->maxsize) {
        pthread_cond_wait(&this->qcond, &this->qlock);
    }
  }
  this->data.push_back(item);
  this->qdone = false;
  pthread_cond_broadcast(&this->qcond);
  pthread_mutex_unlock(&this->qlock);
  return rv;
}

template <class value_type>
int blocking_queue<value_type>::front(value_type *&item) {
  int rv = 0;
  int n;
  pthread_mutex_lock(&this->qlock);
  while(!this->qdone && this->data.empty()) {
    pthread_cond_wait(&this->qcond, &this->qlock);
  }
  if(!(this->data.empty())) {
	  n = this->data.size();
    item = this->data.front();
  } else {
    rv = EWOULDBLOCK;
  }
  pthread_mutex_unlock(&this->qlock);
  return rv;
}

template <class value_type>
int blocking_queue<value_type>::pop() {
  int rv = 0;
  pthread_mutex_lock(&this->qlock);
  if(this->data.empty()) {
    rv = -1;
  } else {
    this->data.pop_front();
  }
  pthread_mutex_unlock(&this->qlock);
  return rv;
}


#endif
