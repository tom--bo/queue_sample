#include "lock_queue.h"

bool UnBoundedMutexLockQueue::enque(long val) {
    bool mustWakeDequeuers = false;
    Node *e = new Node(val);
    pthread_mutex_lock(&enqLock);
    tail->next = e;
    tail = e;
    if(size.fetch_add(1) == 0) {
        mustWakeDequeuers = true;
    }
    pthread_mutex_unlock(&enqLock);
    if(mustWakeDequeuers) {
        pthread_mutex_lock(&deqLock);
        pthread_cond_broadcast(&notEmptyCondition);
        pthread_mutex_unlock(&deqLock);
    }
    return true;
}

bool UnBoundedMutexLockQueue::deque(long &ret) {
    pthread_mutex_lock(&deqLock);
    while(size.load() == 0) {
        pthread_cond_wait(&notEmptyCondition, &deqLock);
    }
    ret = head->next->value;
    head = head->next;
    size.fetch_sub(1);
    pthread_mutex_unlock(&deqLock);
    return true;
}
