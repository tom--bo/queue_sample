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
    UnBoundedLockFreeQueue() {
        CASNode *dummy = new CASNode(-1);
        head.store(dummy);
        tail.store(dummy);
    }

    void enque(long val) {
        CASNode *node = new CASNode(val);
        while(true) {
            CASNode *last = tail.load();
            CASNode *next = last->next.load();
            if(last == tail.load()) {
                if(next == nullptr) {
                    if(last->next.compare_exchange_strong(next, node)) {
                        tail.compare_exchange_strong(last, node);
                        return;
                    }
                } else {
                    tail.compare_exchange_strong(last, next);
                }
            }
        }
    }

    long deque() {
        while(true) {
            CASNode * first = head.load();
            CASNode * last = tail.load();
            CASNode * next = first->next.load();
            if(first == head.load()) {
                if(first == last) {
                    if(next == nullptr) {
                        return -1;
                    }
                    tail.compare_exchange_strong(last, next);
                } else {
                    long value = next->value;
                    if(head.compare_exchange_strong(first, next)) {
                        return value;
                    }
                }
            }
        }
    }
};


#endif//LOCK_FREE_QUEUE_H
