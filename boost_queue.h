#ifndef QUEUE__BOOST_QUEUE_H_
#define QUEUE__BOOST_QUEUE_H_

#include <boost/lockfree/queue.hpp>

class BoostLockFreeQueue {
public:
    boost::lockfree::queue<long, boost::lockfree::capacity<20000> > q;
    int retry;
    BoostLockFreeQueue(int cap_dummy, int retry_cnt): retry(5){
        retry = retry_cnt;
    }

    bool enque(long val) {
        for(int i=0; i<retry; i++) {
            if(q.push(val)) {
                return true;
            }
        }
        return false;
    }

    bool deque(long *ret) {
        for(int i=0; i<retry; i++) {
            if(q.pop(ret)) {
                return true;
            }
        }
        return false;
    }
};


#endif//QUEUE__BOOST_QUEUE_H_
