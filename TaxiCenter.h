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

#include "Cab.h"
#include "LuxuryCab.h"
#include "grid.h"
#include "BFS.h"
#include <vector>
#include <iostream>
#include "Socket.h"
#include "Udp.h"

#include <iostream>
#include <queue>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/deque.hpp>
#include <sstream>

using namespace std;

class TaxiCenter {
private:
    //vector<Driver *> driversInfo;
    vector<int >driversID;
    vector<Cab *> cabsList;
    queue<TripInfo *> tripsList;
   // Statistics *stats;
    Grid* map;
    BFS calculator;
    int freeDrivers;
    Socket* socket;
    queue<Point> createDirections(TripInfo t, Point currentLocation);


    void assignTrips();
    void close();

public:
    TaxiCenter(Grid* grid);
    void setMap(Grid *map);
    void receiveOrder(TripInfo *t);
   //void setStatistics(Statistics *s);
    //Statistics* getStatistics();
    //void addNewDriver(Driver* d);
    void addNewDriver();

    void setSocket(int port, char communicateType);
    
    Point getDriverLocation(int id);
    void addNewCab(Cab *c);
    // Do we want to return the actual object or a copy?
    Cab& getCab(int id);
    void moveOneStep();
    queue<TripInfo *> getTripList();
    ~TaxiCenter();
};


#endif //EX2_TAXICENTER_H
