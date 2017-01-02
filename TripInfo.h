/**
 * Amos Maimon And Or Zipori.
 *
 * TripInfo Header.
 */

#ifndef EX2_TRIPINFO_H
#define EX2_TRIPINFO_H

/**
 * TripInfo Class
 *
 * This class is in charge of the details of the ride.
 */

#include "point.h"
#include "Passenger.h"
#include <queue>
#include <vector>
#include <stdexcept>
#include <boost/serialization/vector.hpp>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/ref.hpp>
#include <boost/serialization/map.hpp>
#include <sstream>

class TripInfo {
private:
    int rideID;
    int meterPassed;
    Point startPoint;
    Point endPoint;
    int numOfPassengers;
    int tariff;
    std::deque<Point> directions;
    std::vector<Passenger> passengers;
    int startTime;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & rideID;
        archive & meterPassed;
        archive & numOfPassengers;
        archive & tariff;
        archive & directions;
        archive & passengers;
        archive & startTime;
        archive & startPoint;
        archive & endPoint;
    }

public:
    TripInfo(){}
    TripInfo(int id, Point start, Point end, std::vector<Passenger> &p, int tarif, int onTime);

    int getMeterPassed();
    void addMeter();
    int getRideID();
    Point getStartPoint();
    Point getEndPoint();
    int getNumPassengers();
    std::deque<Point> getDirections();
    void setDirections(std::queue<Point> d);
    int getTariff();
    void setTime(int t);
    int getTime();
};


//
// change driver : if start time of driver is >= trip info start time
// add to the move of taxi driver the int start time
//

#endif //EX2_TRIPINFO_H
