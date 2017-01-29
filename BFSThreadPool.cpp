//
// Created by amos on 1/29/17.
//



#include "BFSThreadPool.h"
#include "BFSThreadArgs.h"



BFSThreadPool::BFSThreadPool(int threadCount, Grid* map) {
    this->map = map;
    this->advance = true;
    this->threadCount = threadCount;

}
void BFSThreadPool::initialize(){
    int failors = 0;
    // create threads:
    for (int i=0; i < threadCount ; ++i) {
        pthread_t pthread;
        BFSThreadArgs args= BFSThreadArgs();
        args.args = this;
        int errorCheck = pthread_create(&pthread, NULL, startThread, (void*)&args);

        if(errorCheck != 0) {
            LOG(DEBUG) << "Failed to create Thread number  " << i << ".\n";
            ++failors;
        } else {
            this->threads.push_back(pthread);
        }

    }
    // make sure that not wait to thread that Does not exist.
    this->threadCount -= failors;
}

BFSThreadPool::~BFSThreadPool() {
    this->advance = false;
    for (int i = 0 ; i < threadCount; i++) {
        pthread_join(this->threads[i], NULL);
    }
    LOG(INFO) << "BFSThreadPool finished!";
}

void *BFSThreadPool::executeThread() {
    TripInfo* tripInfo = NULL;
    BFS calculator = BFS();
    pthread_mutex_t lock;


    while(this->advance){
        while(this->tripInfoList.empty() && this->advance){sleep(1);}
        pthread_mutex_lock(&lock);
        // make sure that the tripInfo doesn't gets from other thread.
        if ((!this->tripInfoList.empty())&& this->advance) {
            tripInfo = this->tripInfoList.front();
            this->tripInfoList.pop_front();
            // give the other threads to get another trips before start the heavy markCalculated.
            pthread_mutex_unlock(&lock);
            Point startPoint = tripInfo->getStartPoint();
            tripInfo->setDirections(calculator.run(*(this->map), tripInfo->getEndPoint(), &startPoint, 1));
            // mark that the directions are calculate
            tripInfo->markCalculated();
            LOG(INFO) << "TripInfo number " << tripInfo->getRideID() << " is calculated!";
        }

    }
    return NULL;
}

void BFSThreadPool::addTrip(TripInfo *tripInfo) {
    tripInfoList.push_back(tripInfo);
}

BFSThreadPool::BFSThreadPool() {}

void *BFSThreadPool::startThread(void *self) {
    BFSThreadArgs* bfsThreadArgs = (BFSThreadArgs*) self;
    bfsThreadArgs->args->executeThread();

    return NULL;
}
