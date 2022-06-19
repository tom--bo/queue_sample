#ifndef QUEUE__BOOST_QUEUE_H_
#define QUEUE__BOOST_QUEUE_H_

#include <boost/lockfree/queue.hpp>

class BoostLockFreeQueue {
public:
    boost::lockfree::queue<long, boost::lockfree::capacity<20000> > q;
    BoostLockFreeQueue(int) {}

    bool enque(long val);
    bool deque(long &ret);
};


#endif//QUEUE__BOOST_QUEUE_H_
