/**
 * Amos Maimon And Or Zipori.
 *
 */

#ifndef TAXISTATION_DATATYPECLASS_H
#define TAXISTATION_DATATYPECLASS_H

/**
 * DataTypeClass.
 * In charge of being the "arguments" for a void * function.
 */

#include "TripInfo.h"
#include "grid.h"
#include "driverData.h"
#include "TaxiCenter.h"

class DataTypeClass {
public:
    TripInfo *trip;
    vector<Cab *> *cabList;
    map<int, driverData*> *dataMap;
    Grid *g;
    int clientSocketDiscriptor;
    int driverID;
    driverData *data;
    TaxiCenter *self;
    int timeCounter;
    Socket *socket;

    DataTypeClass(){}
};


#endif //TAXISTATION_DATATYPECLASS_H
