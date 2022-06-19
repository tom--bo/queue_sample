#include "boost_queue.h"

bool BoostLockFreeQueue::enque(long val) {
    if(q.push(val)) {
        return true;
    }
    return false;

}
bool BoostLockFreeQueue::deque(long &ret) {
    if(q.pop(ret)) {
        return true;
    }
    return false;
}
