/**
 * Amos Maimon And Or Zipori.
 *
 * TripInfo Implementation.
 */

#include "TripInfo.h"


/**
 * Constructor.
 * @param id
 * @param start
 * @param end
 * @param p
 * @param tarif
 * @return
 */
TripInfo::TripInfo(int id, Point start, Point end, std::vector<Passenger> &p, int tarif, int onTime) {
    if (id < 0) {
        throw std::invalid_argument("Bad ID.");
    }
    if (tarif < 0) {
        throw std::invalid_argument("Bad Tariff");
    }
    if (p.size() < 1) {
        throw std::invalid_argument("Passengers Queue empty");
    }
    rideID = id;
    startTime = onTime;
    startPoint = start;
    endPoint = end;
    while(!p.empty()) {
        Passenger tamp = p.front();
        passengers.push_back(tamp);
        p.pop_back();
    }
    tariff = tarif;
    meterPassed = 0;
    numOfPassengers = (int)passengers.size();

}

/**
 * Get meter passed.
 * @return int
 */
int TripInfo::getMeterPassed() {
    return meterPassed;
}

/**
 * Add meter to the current meter counter.
 */
void TripInfo::addMeter() {
    meterPassed++;
}

/**
 * Get the ride id.
 * @return int
 */
int TripInfo::getRideID() {
    return rideID;
}

/**
 * Get the starting point of the ride.
 * @return Point
 */
Point TripInfo::getStartPoint() {
    return startPoint;
}

/**
 * Get the ending point of the ride.
 * @return
 */
Point TripInfo::getEndPoint() {
    return endPoint;
}

/**
 * Get the number of passengers in the ride.
 * @return int
 */
int TripInfo::getNumPassengers() {
    return numOfPassengers;
}

/**
 * Return the direction for the driver to follow.
 * @return  dequq of Points
 */
std::deque<Point> TripInfo::getDirections() {
    return directions;
}

/**
 * Get the tariff.
 * @return int
 */
int TripInfo::getTariff() {
    return tariff;
}

/**
 * Set the direction of the ride.
 * @param directions
 */
void TripInfo::setDirections(std::queue<Point> d) {
    // Emptying the current queue
    while(!directions.empty()) {
        directions.pop_back();
    }

    // Getting newer queue
    d.pop(); // remove the driver start point
    while(!d.empty()) {
        directions.push_back(d.front());
        d.pop();
    }
}

/**
 * Set start time.
 *
 * @param t
 */
void TripInfo::setTime(int t) {
    startTime = t;
}

/**
 * Get start time.
 * @return int
 */
int TripInfo::getTime(){
    return startTime;
}
/**
 * Get trip info thread.
 * @return pthread_t
 */
pthread_t& TripInfo::getThread() {
    return BFSthread;
}