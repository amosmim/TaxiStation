//
// Created by guest on 1/15/17.
//

#ifndef TAXISTATION_DRIVERDATA_H
#define TAXISTATION_DRIVERDATA_H

#include <pthread.h>

// Grouping driver client data
struct driverData
{
    int driverID;
    int driversDescriptors;
    pthread_t driverThread;
};

#endif //TAXISTATION_DRIVERDATA_H
