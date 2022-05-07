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

class UnBoundedQueue {
public:
    pthread_mutex_t enqLock, deqLock;
    pthread_cond_t notEmptyCondition;
    std::atomic<int> size;
    Node *head, *tail;
    UnBoundedQueue(): size(0) {
        head = new Node(0);
        tail = head;
        pthread_mutex_init(&enqLock, NULL);
        pthread_mutex_init(&deqLock, NULL);
    }

    void enque(long val) {
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
    }

    long deque() {
        long result;
        pthread_mutex_lock(&deqLock);
        while(size.load() == 0) {
            pthread_cond_wait(&notEmptyCondition, &deqLock);
        }
        result = head->next->value;
        head = head->next;
        size.fetch_sub(1);
        pthread_mutex_unlock(&deqLock);
        return result;
    }
};



#endif//QUEUE_LOCK_QUEUE_H
