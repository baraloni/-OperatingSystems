#ifndef BARRIER_H
#define BARRIER_H
#include <pthread.h>

// a multiple use barrier

class Barrier {
public:
    /**
     * Creates a new barrier object.
     * @param numThreads: The number of thread doing the map reduce job.
     */
    Barrier(int numThreads);
    ~Barrier();

    /**
     * A thread calling this meathod after doing some task will have to wait to the other threads
     * to finish the same task.
     */
    void barrier();

private:
    pthread_mutex_t mutex;
    pthread_cond_t cv;
    int count;
    int numThreads;
};

#endif //BARRIER_H
