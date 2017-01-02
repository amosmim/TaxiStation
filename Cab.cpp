/**
 * Amos Maimon And Or Zipori.
 *
 * Cab Implementaion.
 */

#include "Cab.h"
/**
 * Cab Constractor
 */
Cab::Cab() {
    meterPassed = 0;
    //velocity = 0; // Speed of cab
}

/**
 * Get the meter number of the cab.
 * @return int
 */
int Cab::getMeterPassed() {
    return meterPassed;
}

/**
 * Get the tariff of the cab.
 * @return int
 */
int Cab::getTariff() {
    return tariff;
}

/**
 * Add meter to the current meter indicator.
 * @param meter
 */
void Cab::addMeter(int meter) {
    meterPassed =+ meter;
}

/**
 * Get the id of the cab.
 * @return int
 */
int Cab::getID() {
    return cabID;
}

