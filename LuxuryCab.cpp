/**
 * Amos Maimon And Or Zipori.
 *
 * LuxuryCab Implementation.
 */

#include "LuxuryCab.h"

/**
 * Constructor.
 * @param id id number
 * @param t CarType
 * @param c CarColor
 * @param tariff tariff of to cab
 *
 */
LuxuryCab::LuxuryCab(int id, CarType t, CarColor c, int tariff){
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
 * Returning the number of blocks a luxury cab can go.
 * @return int
 */
int LuxuryCab::canMove() {
    return 2;
}
