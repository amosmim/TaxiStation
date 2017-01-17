//
// Created by guest on 1/15/17.
//

#ifndef TAXISTATION_DRIVERDATA_H
#define TAXISTATION_DRIVERDATA_H

#include <pthread.h>
#include "point.h"

// Grouping driver client data
struct driverData
{
    int driverID;
    int driversDescriptors;
    Point location;
    pthread_t driverThread;
};

#endif //TAXISTATION_DRIVERDATA_H
