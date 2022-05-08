#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <chrono>
#include "lock_queue.h"
#include "cas_queue.h"
#include "boost_queue.h"
using namespace std;

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
int objects_limit_per_thread;
int thread_count = 1;

template<class T>
void *producer(void *) {
    long *failed_count = (long *)malloc(sizeof(long));
    *failed_count = 0;
    pthread_mutex_lock(&producer_blocker->mu);
    if(is_all_runnerble == false) {
        pthread_cond_wait(&producer_blocker->cond, &producer_blocker->mu);
    }
    pthread_mutex_unlock(&producer_blocker->mu);
    for(int i = 1; i <= objects_limit_per_thread; i++) {
        if(q<T>->enque(i) == false) {
            (*failed_count)++;
            i--;
            continue;
        }
    }
    return failed_count;
}

template<class T>
void *consumer(void *ret) {
    long tmp;
    long *sum = (long *)ret;
    while(true) {
        if(q<T>->deque(tmp) == false) {
            continue;
        }
        if(tmp == -1) break;
        *sum += tmp;
    }
    return nullptr;
}


template<class T>
void enqueue_benchmark() {
    cout << "[START] enqueue benchmark" << endl;
    int capacity = 1000;
    q<T> = new T(capacity);
    // timer start
    vector<pthread_t> th = *(new vector<pthread_t>(thread_count));

    // start producer threads
    for(int i = 0; i < thread_count; i++) {
        pthread_create(&th[i], NULL, producer<T>, nullptr);
    }
    auto start = chrono::system_clock::now();
    pthread_mutex_lock(&producer_blocker->mu);
    is_all_runnerble = true;
    pthread_cond_broadcast(&producer_blocker->cond);
    pthread_mutex_unlock(&producer_blocker->mu);
    // wait threads
    long failed_total = 0;
    for(int i = 0; i < thread_count; i++) {
        void *ret;
        if(pthread_join(th[i], &ret) != 0) {
            exit(1);
        }
        long failed_count = *(long *)ret;
        failed_total += failed_count;
    }

    // timer stop
    auto end = chrono::system_clock::now();
    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout << "elapsed: " << msec << " ms (" << thread_count << " threads enqued " << objects_limit_per_thread << " each)\n";
    cout << "failed_total: " << failed_total << endl;

    // check contents
    q<T>->enque(-1);
    long sum = 0;
    consumer<T>(&sum);
    // print result
    cout << sum << endl;
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout << "[ERROR] invalid arguments: " << endl;
        cout << "(help) " << argv[0] << " {queue_type_number} {objects per thread} {thread_cnt}" << endl;
        cout << "queue_type_number = 1~3" << endl;
        cout << "  1: UnboundedMutexQueue" << endl;
        cout << "  2: UnboundedLockFreeQueue" << endl;
        // cout << "  3: BoostLockFreeQueue" << endl;
        return 1;
    }
    int queue_type_num = stoi(argv[1]);
    objects_limit_per_thread = stoi(argv[2]);
    thread_count = stoi(argv[3]);

    switch(queue_type_num) {
        case 1:
            enqueue_benchmark<UnBoundedMutexLockQueue>();
            break;
        case 2:
            enqueue_benchmark<UnBoundedLockFreeQueue>();
            break;
        // case 3:
        //     enqueue_benchmark<BoostLockFreeQueue>();
        //     break;
        default:
            cout << "[ERROR] queue_type_number should be 1~3." << endl;
    }

    return 0;
}
