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
};


#endif //EX2_TRIPINFO_H
