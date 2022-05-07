#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include "lock_queue.h"
#include "cas_queue.h"

#define LIMIT 100000
#define PRODUCER_TH_CNT 100


struct starter_block {
    pthread_mutex_t mu;
    pthread_cond_t cond;
    starter_block() {
        pthread_mutex_init(&mu, nullptr);
        pthread_cond_init(&cond, nullptr);
    }
};
// global variables
starter_block *producer_blocker = new starter_block();
template <class T> T *q;
bool is_all_runnerble = false;

template<class T>
void *producer(void *) {
    pthread_mutex_lock(&producer_blocker->mu);
    if(is_all_runnerble == false) {
        pthread_cond_wait(&producer_blocker->cond, &producer_blocker->mu);
    }
    pthread_mutex_unlock(&producer_blocker->mu);
    for(int i = 1; i <= LIMIT; i++) {
        q<T>->enque(i);
    }
    return nullptr;
}

template<class T>
void *consumer(void *ret) {
    long tmp;
    long *sum = (long *)ret;
    while(true) {
        tmp = q<T>->deque();
        if(tmp == -1) break;
        *sum += tmp;
    }
    return nullptr;
}


template<class T>
void enqueue_benchmark() {
    q<T> = new T();
    // timer start
    pthread_t th[PRODUCER_TH_CNT] = {};
    // start producer threads
    for(int i = 0; i < PRODUCER_TH_CNT; i++) {
        pthread_create(&th[i], NULL, producer<T>, nullptr);
    }
    auto start = std::chrono::system_clock::now();
    pthread_mutex_lock(&producer_blocker->mu);
    is_all_runnerble = true;
    pthread_cond_broadcast(&producer_blocker->cond);
    pthread_mutex_unlock(&producer_blocker->mu);
    // wait threads
    for(int i = 0; i < PRODUCER_TH_CNT; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            exit(1);
        }
    }

    // timer stop
    auto end = std::chrono::system_clock::now();
    auto dur = end - start;
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cout << msec << " milli sec \n";

    // check contents
    q<T>->enque(-1);
    long sum = 0;
    consumer<T>(&sum);
    // print result
    std::cout << sum << std::endl;
}

int main() {
    std::cout << "start" << std::endl;
//    enqueue_benchmark<UnBoundedQueue>();
    enqueue_benchmark<UnBoundedLockFreeQueue>();
    return 0;
}
