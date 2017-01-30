//
// Created by amos on 1/29/17.
//

#ifndef TAXISTATION_BFSTHREADPOOL_H
#define TAXISTATION_BFSTHREADPOOL_H
#include <sys/param.h>
#include <pthread.h>
#include <boost/serialization/vector.hpp>
#include "grid.h"

#include "TripInfo.h"
#include "BFS.h"
#include "easylogging++.h"

class BFSThreadPool {

public:
    BFSThreadPool();
    BFSThreadPool(int threadCount, Grid* map);
    ~BFSThreadPool();
    void initialize();

    void addTrip(TripInfo* tripInfo);
    static void* startThread(void* self);
    void* executeThread();

private:
    Grid* map;
    pthread_mutex_t lock;
    int threadCount;
    pthread_t* threads;
    std::deque<TripInfo*> tripInfoList;



    bool advance;

};



#endif //TAXISTATION_BFSTHREADPOOL_H
