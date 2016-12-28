/**
 * Amos Maimon And Or Zipori.
 *
 * Passenger Header.
 */

#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

/**
 * Passenger Class.
 *
 * Represents the passengers that requires trips over the grid.
 */

#include "point.h"
#include <stdlib.h>

class Passenger {
private:
    Point startPoint;
    Point endPoint;
public:
    Passenger(Point s, Point e);
    Point getStartPoint();
    Point getEndPoint();
    int generateScore();
};


#endif //EX2_PASSENGER_H
