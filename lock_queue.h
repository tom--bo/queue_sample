#ifndef QUEUE_LOCK_QUEUE_H
#define QUEUE_LOCK_QUEUE_H

#include <atomic>
#include <pthread.h>

class Node {
public:
    long value;
    Node *next;
    Node(long v) {
        value = v;
        next = nullptr;
    }
};

class UnBoundedMutexLockQueue {
public:
    pthread_mutex_t enqLock, deqLock;
    pthread_cond_t notEmptyCondition;
    std::atomic<int> size;
    Node *head, *tail;
    UnBoundedMutexLockQueue(int): size(0) {
        head = new Node(0);
        tail = head;
        pthread_mutex_init(&enqLock, NULL);
        pthread_mutex_init(&deqLock, NULL);
    }

    bool enque(long val);
    bool deque(long &ret);
};

#endif//QUEUE_LOCK_QUEUE_H
