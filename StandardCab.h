/**
 * Amos Maimon And Or Zipori.
 *
 * StandardCab Header.
 */

#ifndef EX2_STANDARDCAB_H
#define EX2_STANDARDCAB_H

/**
 * Standard Cab Class.
 *
 * A standard cab.
 */

#include "Cab.h"

class StandardCab : public Cab {
public:
    StandardCab (int id, CarType t, CarColor c, int tariff);
    int canMove();
};


#endif //EX2_STANDARDCAB_H
