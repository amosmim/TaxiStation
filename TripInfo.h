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
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/serialization/vector.hpp>

class TripInfo {
private:
    int rideID;
    int meterPassed;
    Point startPoint;
    Point endPoint;
    int numOfPassengers;
    int tariff;
    std::queue<Point> directions;
    std::vector<Passenger> passengers;
    int startTime;
public:
    TripInfo(int id, Point start, Point end, std::vector<Passenger> &p, int tarif);
    int getMeterPassed();
    void addMeter();
    int getRideID();
    Point getStartPoint();
    Point getEndPoint();
    int getNumPassengers();
    std::queue<Point> getDirections();
    void setDirections(std::queue<Point> d);
    int getTariff();
    void setTime(int t);
    int getTime();
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version);
};


//
// change driver : if start time of driver is >= trip info start time
// add to the move of taxi driver the int start time
//

#endif //EX2_TRIPINFO_H
