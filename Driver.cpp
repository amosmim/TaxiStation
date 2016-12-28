/**
 * Amos Maimon And Or Zipori.
 *
 * Driver Implementation.
 */

#include "Driver.h"

/**
 * Constructor.
 * @param id driverId
 * @param dAge age of driver
 * @param s  status
 * @param exp exprience years
 * @param v_id
 * @param stat Statistics observer
 */
Driver::Driver(int id, int dAge, Status s, int exp, int v_id, Statistics *stat) {
    if (id < 0) {
        throw std::invalid_argument("Bad ID.");
    }
    if (dAge < 0) {
        throw std::invalid_argument("Bad Age");
    }
    driverID =id;
    age = dAge;
    status = s;
    yearsOfExprience = exp;
    avgSatisfaction = 0;
    votesNumber = 0;
    vehicleID = v_id;
    stats = stat;
    setCurrentLocation(Point(0,0));
    availalbe = true;
}

/**
 * setter to current Location
 * @param p point
 */
void Driver::setCurrentLocation(Point p) {
    // update statistic observer
    stats->setData(driverID, p);
    // move the driver to P point.
    currentLocation = p;
}

/**
 * getter to currentLocation
 * @return the current Location of the driver.
 */
Point Driver::getCurrentLocation() {
    return currentLocation;
}

/**
 * getter to Satisfaction average.
 * @return double - Satisfaction average.
 */
double Driver::getSatisfaction() {
    return avgSatisfaction;
}

/**
 * Add more Satisfaction vote.
 * @param rank Satisfaction vote
 */
void Driver::addScore(int rank) {
    if (rank > 5) {
        throw std::invalid_argument("invalid number");
    }
    votesNumber++;
    avgSatisfaction = (avgSatisfaction + rank) / votesNumber;
}

/**
 * move one step (according to the cab speed)
 * @return
 */
bool Driver::driveTo() {
    if (!availalbe) {
        // check who mach the cab can go in one step.
        int canGo = cab->canMove();

        // while there still way to go, and the cab can move in this step.
        while ((!wayLeft.empty()) && (canGo > 0)) {
            setCurrentLocation(wayLeft.front());
            wayLeft.pop();
            canGo--;
        }
        // update the Meter counter in the cab.
        cab->addMeter(cab->canMove() - canGo);
        // check if the trip as finished.
        if (wayLeft.empty()) {
            availalbe = true;
            delete (tripInfo);
        }

    }
    return availalbe;
}

void Driver::setStatus(Status stat) {
    status = stat;
}

/**
 * getter to driver status.
 * @return Status
 */
Status Driver::getStatus() {
    return status;
}

/**
 * getter to driver ID
 * @return ID of he driver
 */
int Driver::getID() {
    return driverID;
}

/**
 * get driver age.
 * @return driver age.
 */
int Driver::getAge() {
    return age;
}

/**
 * Get vehicle id
 * @return int
 */
int Driver::getVehicleID() {
    return vehicleID;
}

/**
 * give the driver a cab.
 * @param cab
 */
void Driver::setCab(Cab *cab) {
    Driver::cab = cab;
}


/**
 * return if the driver is available
 * @return bool
 */
bool Driver::isAvailable() {
    return availalbe;
}

/**
 * give the driver trip info
 * @param t TripInfo
 */
void Driver::setTripInfo(TripInfo *t) {
    tripInfo = t;
    availalbe = false;
    wayLeft = tripInfo->getDirections();
    // remove the driver start point
    wayLeft.pop();
}

/**
 * Serialization of the object.
 * @param archive
 * @param version
 */
template<class Archive>
void Driver::serialize(Archive& archive, const unsigned int version)
{
    archive & BOOST_SERIALIZATION_NVP(driverID);
    archive & BOOST_SERIALIZATION_NVP(age);
    archive & BOOST_SERIALIZATION_NVP(yearsOfExprience);
    archive & BOOST_SERIALIZATION_NVP(avgSatisfaction);
    archive & BOOST_SERIALIZATION_NVP(votesNumber);
    archive & BOOST_SERIALIZATION_NVP(tripInfo);
    archive & BOOST_SERIALIZATION_NVP(status);
    archive & BOOST_SERIALIZATION_NVP(currentLocation);
    archive & BOOST_SERIALIZATION_NVP(vehicleID);
    archive & BOOST_SERIALIZATION_NVP(availalbe);
    archive & BOOST_SERIALIZATION_NVP(cab);
    archive & BOOST_SERIALIZATION_NVP(wayLeft);
    archive & BOOST_SERIALIZATION_NVP(cab);

    // how serialize it...it's a single class !!
    //Statistics *stats;
}