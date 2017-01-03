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
#include <deque>
#include "TripInfo.h"
#include "Cab.h"
#include "Statistics.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/ref.hpp>
#include <boost/serialization/map.hpp>
#include <sstream>

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
    //Statistics *stats;
    bool availalbe;
    deque<Point> wayLeft;
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive& archive, const unsigned int version) const{
        archive & driverID;
        archive & age;
        archive & yearsOfExprience;
        archive & avgSatisfaction;
        archive & votesNumber;
        archive & tripInfo;
        archive & status;
        archive & currentLocation;
        archive & vehicleID;
        archive & availalbe;
        archive & cab;
        archive & wayLeft;
    }
    template<class Archive>
    void load(Archive& archive, const unsigned int version){
        archive & driverID;
        archive & age;
        archive & yearsOfExprience;
        archive & avgSatisfaction;
        archive & votesNumber;
        archive & tripInfo;
        archive & status;
        archive & currentLocation;
        archive & vehicleID;
        archive & availalbe;
        archive & cab;
        archive & wayLeft;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
    Driver() {}
    ~Driver();
    Driver(int id, int dAge, Status s, int exp, int v_id, Statistics *stat);
    Driver(int id, int dAge, Status s, int exp, int v_id);
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
    Cab* getCab();
};


#endif //EX2_DRIVER_H
