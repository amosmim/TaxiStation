/**
 * Amos Maimon And Or Zipori.
 *
 * StandardCab Implementation.
 */

#include "StandardCab.h"

/**
 * Constructor.
 * @param id ID number
 * @param t CarType
 * @param c CarColor
 * @param tariff
 * @return StandardCab
 */
StandardCab::StandardCab(int id, CarType t, CarColor c, int tariff) {
    if (id < 0) {
        throw std::invalid_argument("Bad ID.");
    }
    if (tariff < 0) {
        throw std::invalid_argument("Bad Tariff");
    }
    this->tariff = tariff;
    this->carColor = c;
    this->carType = t;
    this->cabID = id;
}

/**
 * Returning the number of blocks a standard cab can go.
 * @return int
 */
int StandardCab::canMove() {
    return 1;
}

BOOST_CLASS_EXPORT(StandardCab)