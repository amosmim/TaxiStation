/**
 * Amos Maimon And Or Zipori.
 *
 * Passenger Implementation.
 */


#include "Passenger.h"

/**
 * Contractor.
 * @param s start point
 * @param e end point
 */
Passenger::Passenger(Point s, Point e) {
    startPoint = s;
    endPoint = e;
}

/**
 * Get starting point.
 * @return Point
 */
Point Passenger::getStartPoint() {
    return startPoint;
}

/**
 * Get ending point.
 * @return Point
 */
Point Passenger::getEndPoint() {
    return endPoint;
}

/**
 * Generate a random score for the driver.
 * @return
 */
int Passenger::generateScore() {
    return rand() % 5 + 1;
}
