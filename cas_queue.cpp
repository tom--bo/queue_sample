#include "cas_queue.h"

bool UnBoundedLockFreeQueue::enque(long val) {
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

bool UnBoundedLockFreeQueue::deque(long &ret) {
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
