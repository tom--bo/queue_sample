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

    bool enque(long val) {
        CASNode *node = new CASNode(val);
        for(int i = 0; i < 5; i++) {
            CASNode *last = tail.load();
            CASNode *next = last->next.load();
            if(last == tail.load()) {
                if(next == nullptr) {
                    if(last->next.compare_exchange_strong(next, node)) {
                        tail.compare_exchange_strong(last, node);
                        return true;
                    }
                } else {
                    tail.compare_exchange_strong(last, next);
                }
            }
        }
        return false;
    }

    bool deque(long &ret) {
        CASNode * first = head.load();
        CASNode * last = tail.load();
        CASNode * next = first->next.load();
        if(first == head.load()) {
            if(first == last) {
                if(next == nullptr) {
                    return false;
                }
                tail.compare_exchange_strong(last, next);
            } else {
                ret = next->value;
                if(head.compare_exchange_strong(first, next)) {
                    return true;
                }
            }
        }
        return false;
    }
};


#endif//LOCK_FREE_QUEUE_H
