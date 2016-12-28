/**
 * Amos Maimon And Or Zipori.
 *
 * TaxiCenter Implementation.
 */

#include "TaxiCenter.h"

/**
 * Constructor.
 * @param grid
 * @return
 */
TaxiCenter::TaxiCenter(Grid* grid) {
    map = grid;
}

/**
 * Receive the order from the client and set the direction.
 *
 * @param t
 */
void TaxiCenter::receiveOrder(TripInfo *t) {
    Point start = t->getStartPoint();
    t->setDirections(calculator.run(*map, t->getEndPoint(), &start, 1));
    tripsList.push(t);
}

/**
 * Set the statistics instance for the current run.
 * @param s
 */
void TaxiCenter::setStatistics(Statistics *s) {
    stats = s;
}

/**
 * Get the statistics instance.
 * @return Statistics
 */
Statistics* TaxiCenter::getStatistics() {
    return stats;
}

/**
 * Add a new driver to the station.
 * @param d
 */
void TaxiCenter::addNewDriver(Driver* d) {
    for (int j = 0; j < cabsList.size(); j++) {
        if (cabsList[j]->getID() == d->getVehicleID()) {
            d->setCab(cabsList[(size_t) j]); //get cab id inside driver
        }
    }
    driversInfo.push_back(d);
}

/**
 * Search for driver by driver id.
 *
 * @param id
 * @return If found return Driver instance, else not found exception.
 */
Driver TaxiCenter::getDriver(int id) {
    for (int i = 0; i < driversInfo.size(); i++) {
        if (driversInfo[i]->getID() == id) {
            return *driversInfo[i];
        }
    }

    // throw exception
    throw std::invalid_argument("Not exist.");
}

/**
 * Add a new cab to the station.
 * @param c
 */
void TaxiCenter::addNewCab(Cab *c) {
    cabsList.push_back(c);
}

/**
 * Get the queue of the trips.
 * @return queue
 */
queue<TripInfo *> TaxiCenter::getTripList() {
    return tripsList;
}

/**
 * Union of two routes.
 *
 * @param t
 * @param currentLocation
 * @return the union route
 */
queue<Point> TaxiCenter::createDirections (TripInfo t, Point currentLocation) {
    queue<Point> from = calculator.run(*map, t.getStartPoint(), &currentLocation, 1);
    Point start = t.getStartPoint();
    queue<Point> to = calculator.run(*map, t.getEndPoint(), &start, 1);
    Point tamp;

    // We don't want two points that are equal, because the first point in to
    // and the last point in from are the same
    to.pop();
    while (!to.empty()) {
        tamp = to.front();
        from.push(tamp);
        to.pop();
    }

    return from;
}

/**
 * Search for cab by cab id.
 *
 * @param id
 * @return If found return Cab instance, else not found exception.
 */
Cab& TaxiCenter::getCab(int id) {
    for (int i = 0; i < cabsList.size(); i++) {
        if (cabsList[i]->getID() == id) {
            return *cabsList[i];
        }
    }

    // throw exception
    throw std::invalid_argument("Not exist.");
    //Cab* cab = new LuxuryCab(1,CarType::FIAT, CarColor::RED, 100);
    //return *cab;
}

/**
 * Move the taxi drivers around for their objectives.
 *
 * @return true if all drivers finnised.
 */
bool TaxiCenter::start() {
    int driversCount;
    freeDrivers = 0;
    for (int j = 0; j < driversInfo.size(); j++) {
        if (driversInfo[j]->isAvailable()) {
            freeDrivers++;
        }
    }
    vector<Driver *> tamp;
    Point driverPlace;
    // Assign trip to driver
    while(!tripsList.empty()){
        if (driversInfo.size() < tripsList.size()) {
            throw std::invalid_argument("To Much Trips");
        }
        for (int i = 0; i < driversInfo.size(); i++) {
            TripInfo *t = tripsList.front();
            driverPlace = stats->getLocationByID(driversInfo[i]->getID());
            if ((driverPlace == t->getStartPoint())&&(driversInfo[i]->isAvailable())) {
                t->setDirections(createDirections(*t, driverPlace));
                driversInfo[i]->setTripInfo(t);
                tripsList.pop();
                tamp.push_back(driversInfo[i]);

            }
        }
    }

    // Make the drivers start driving
    int i = 0;
    while(!tamp.empty()) {
        if(tamp[i]->driveTo()) {
            tamp.erase(tamp.begin() + i);
        }
        i++;
        if (i >= tamp.size()) {
            i = 0;
        }
    }

    // Finished
    return true;
}


/**
 * Set the grid which the taxi center operates on.
 * @param map
 */
void TaxiCenter::setMap(Grid *map) {
    TaxiCenter::map = map;
}

/**
 * Destructor.
 */
TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < cabsList.size(); i++) {
        delete(cabsList[i]);
    }
    for (int i = 0; i < driversInfo.size(); i++) {
        delete(driversInfo[i]);
    }
}
