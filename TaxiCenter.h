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
#include "Commends.h"

#include "Cab.h"
#include "LuxuryCab.h"
#include "grid.h"
#include "BFS.h"
#include <vector>
#include <iostream>
#include "Socket.h"
#include "Tcp.h"

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
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/deque.hpp>
#include <sstream>
#include <sys/socket.h>
#include <pthread.h>

using namespace std;

class TaxiCenter {
private:

    std::map<int, struct driverData*> dataMap;
    vector<Cab *> cabsList;
    vector<TripInfo *> tripsList;
    Grid* map;
    BFS calculator;
    Socket* socket;
    int timeCounter;

    void close();

    Point getDriverLocation(int id);

public:
    TaxiCenter(Grid* grid);

    static void* doOneStepThreaded(void *data);
    static void* addNewDriverThreaded(void *data);
    void receiveOrder(TripInfo *t);
    void addNewDriver();
    void setSocket(int port, char communicateType);
    Point driverLocation(int id);
    void addNewCab(Cab *c);
    void moveOneStep();
    void waitForThreads();
    ~TaxiCenter();
};


#endif //EX2_TAXICENTER_H
