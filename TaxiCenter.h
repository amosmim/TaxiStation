/**
 * Amos Maimon And Or Zipori.
 *
 * TaxiCenter Header.
 */

#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

/**
 * TaxiCenter Class.
 *
 * In charge of getting client's order and dispatching available taxi drivers
 * to their trips.
 */

#include "Statistics.h"
#include "TripInfo.h"
#include "Driver.h"
#include "Cab.h"
#include "LuxuryCab.h"
#include "grid.h"
#include "BFS.h"
#include <vector>
#include <iostream>

using namespace std;

class TaxiCenter {
private:
    vector<Driver *> driversInfo;
    vector<Cab *> cabsList;
    queue<TripInfo *> tripsList;
    Statistics *stats;
    Grid* map;
    BFS calculator;
    int freeDrivers;
    struct sockaddr_in *from;

    queue<Point> createDirections(TripInfo t, Point currentLocation);




public:
    TaxiCenter(Grid* grid);
    void setMap(Grid *map);
    void receiveOrder(TripInfo *t);
    void setStatistics(Statistics *s);
    Statistics* getStatistics();
    void addNewDriver(Driver* d);
    void addNewDriver(Driver* d, struct sockaddr_in *fromi);
    Driver getDriver(int id);
    void addNewCab(Cab *c);
    // Do we want to return the actual object or a copy?
    Cab& getCab(int id);

    bool start();
    queue<TripInfo *> getTripList();
    ~TaxiCenter();
};


#endif //EX2_TAXICENTER_H
