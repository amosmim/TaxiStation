/**
 * Amos Maimon And Or Zipori.
 *
 * Cab Header.
 */

#ifndef EX2_CAB_H
#define EX2_CAB_H

/**
 * Cab Class.
 *
 * An absract class which is a base class for Luxury and Standard cabs.
 */

#include "CarType.h"
#include "CarColor.h"
#include <stdexcept>

class Cab {
private:
    int meterPassed;
protected:
    int cabID;
    CarType carType;
    CarColor carColor;
    int tariff;
public:
    Cab();
    int getMeterPassed();
    int getTariff();
    int getID();
    virtual int canMove() = 0;
    // void setTariff(int t);
    void addMeter(int meter);
};

#endif //EX2_CAB_H
