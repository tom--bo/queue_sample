#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "lock_queue.h"
#include "cas_queue.h"

#define LIMIT 10000
#define PRODUCER_TH_CNT 20

template<class T>
void *producer(void *queue) {
    T *q = (T *)queue;
    for(int i = 1; i <= LIMIT; i++) {
        q->enque(i);
    }
}

template<class T>
void *consumer(void *queue) {
    T *q = (T *)queue;
    long tmp;
    long sum = *(long*)(malloc(sizeof(long)));
    sum = 0;
    while(true) {
        tmp = q->deque();
        if(tmp == -1) break;
        sum += tmp;
    }
    return (void*)&sum;
}

template<class T>
void benchmark() {
    // timer start
    auto start = std::chrono::system_clock::now();
    auto q = new T();
    pthread_t th[PRODUCER_TH_CNT] = {};
    // start procucer threads
    for(int i = 0; i < PRODUCER_TH_CNT; i++) {
        pthread_create(&th[i], NULL, producer<T>, q);
    }
    // wait threads
    for(int i = 0; i < PRODUCER_TH_CNT; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            exit(1);
        }
    }
    q->enque(-1);

    long sum = *(long*)consumer<T>(q);

    // timer stop
    auto end = std::chrono::system_clock::now();
    auto dur = end - start;
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cout << msec << " milli sec \n";

    // print result
    std::cout << sum << std::endl;
}

int main() {
    std::cout << "start" << std::endl;
    benchmark<UnBoundedQueue>();
//    benchmark<UnBoundedLockFreeQueue>();
    return 0;
}
