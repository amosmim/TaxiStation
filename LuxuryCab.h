/**
 * Amos Maimon And Or Zipori.
 *
 * LuxuryCab Header.
 */


#ifndef EX2_LUXURYCAB_H
#define EX2_LUXURYCAB_H

/**
 * LuxuryCab class.
 *
 * Represents the luxury cab.
 */

#include "Cab.h"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

class LuxuryCab : public Cab {
public:
    LuxuryCab (int id, CarType t, CarColor c, int tariff);
    int canMove();
};


#endif //EX2_LUXURYCAB_H
