//
// Created by amos on 1/29/17.
//



#include "BFSThreadPool.h"




BFSThreadPool::BFSThreadPool(int threadCount, Grid* map) {
    this->map = map;
    this->advance = true;
    this->threadCount = threadCount;
    this->threads = new pthread_t[threadCount];

}
void BFSThreadPool::initialize(){

    pthread_mutex_init(&lock, NULL);
    // create threads:
    for (int i=0; i < threadCount ; ++i) {

        //BFSThreadArgs args= BFSThreadArgs();
        //args.args = this;
        LOG(INFO) << "create BFS Thread no. " << i;
        int errorCheck = pthread_create(threads + i, NULL, startThread, this);

        if(errorCheck != 0) {
            LOG(DEBUG) << "Failed to create Thread number  " << i << ".\n";
        }

    }
    LOG(DEBUG) << "finish initialize";

}

BFSThreadPool::~BFSThreadPool() {
    this->advance = false;

    for (int i = 0 ; i < threadCount; i++) {
        pthread_join(this->threads[i], NULL);
    }
    delete[] threads;
    pthread_mutex_destroy(&lock);
    LOG(INFO) << "BFSThreadPool finished!";
}

void *BFSThreadPool::executeThread() {
    LOG(DEBUG) << "start executeThread()";
    TripInfo* tripInfo = NULL;
    BFS calculator = BFS();


    while(this->advance){
        //LOG(INFO) << "in while.";
        //while(this->tripInfoList.empty() && this->advance){sleep(1);}
        pthread_mutex_lock(&lock);
        // make sure that the tripInfo doesn't gets from other thread.
        if ((!this->tripInfoList.empty()) && this->advance) {
            tripInfo = this->tripInfoList.front();
            LOG (INFO) << "Thread pop trip no. " << tripInfo->getRideID();
            this->tripInfoList.pop_front();
            // give the other threads to get another trips before start the heavy markCalculated.
            pthread_mutex_unlock(&lock);
            Point startPoint = tripInfo->getStartPoint();
            tripInfo->setDirections(calculator.run(*(this->map), tripInfo->getEndPoint(), &startPoint, 1));
            // mark that the directions are calculate
            tripInfo->markCalculated();
            LOG(INFO) << "TripInfo number " << tripInfo->getRideID() << " is calculated!";
        }else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

    }
    return NULL;
}

void BFSThreadPool::addTrip(TripInfo *tripInfo) {
    LOG(DEBUG) << "tripinfo no. " << tripInfo->getRideID() << " add to Threads Poll";
    tripInfoList.push_back(tripInfo);
}


void *BFSThreadPool::startThread(void *self) {
    LOG(DEBUG)<< "in startThread()";
    BFSThreadPool* pool = (BFSThreadPool*) self;
    //BFSThreadArgs* bfsThreadArgs = (BFSThreadArgs*) self;
    //bfsThreadArgs->args->executeThread();
    pool->executeThread();

    return NULL;
}
