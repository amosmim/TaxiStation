/**
 * Amos Maimon And Or Zipori.
 *
 * Driver Header.
 */

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

/**
 * Driver Class.
 *
 * This class is in charge to represent the driver in the game, including
 * the driving method which makes the driver go from point to point.
 */
#include "Status.h"
#include <vector>
#include "TripInfo.h"
#include "Cab.h"
#include "Statistics.h"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/queue.hpp>
#include <iostream>
#include <fstream>

using namespace std;
class Driver {
private:
    int driverID;
    int age;
    Status status;
    int yearsOfExprience;
    double avgSatisfaction;
    int votesNumber;
    TripInfo* tripInfo ;
    Point currentLocation;
    Cab *cab;
    int vehicleID;
    Statistics *stats;
    bool availalbe;
    queue<Point> wayLeft;
public:
    Driver() {}
    Driver(int id, int dAge, Status s, int exp, int v_id, Statistics *stat);
    void setCab(Cab *cab);
    void setCurrentLocation(Point p);
    Point getCurrentLocation();
    double getSatisfaction();
    void addScore(int rank);
    // Should be boolean?
    bool driveTo();
    void setStatus(Status status);
    Status getStatus();
    int getID();
    int getAge();
    int getVehicleID();
    bool isAvailable();
    void setTripInfo(TripInfo *t);
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version);
};


#endif //EX2_DRIVER_H
