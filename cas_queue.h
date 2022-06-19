#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>

class CASNode {
public:
    long value;
    std::atomic<CASNode *> next{nullptr};
    CASNode(long v) {
        value = v;
    }
};

class UnBoundedLockFreeQueue {
public:
    std::atomic<CASNode *> head, tail;
    UnBoundedLockFreeQueue(int) {
        CASNode *dummy = new CASNode(-1);
        head.store(dummy);
        tail.store(dummy);
    }

    bool enque(long val);
    bool deque(long &ret);
};


#endif//LOCK_FREE_QUEUE_H
