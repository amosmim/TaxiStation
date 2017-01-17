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
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <sstream>

class Cab {
private:
    int meterPassed;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & cabID;
        archive & meterPassed;
        archive & carType;
        archive & carColor;
        archive & tariff;
        archive & velocity;
    }
protected:
    int cabID;
    CarType carType;
    CarColor carColor;
    int tariff;
    int velocity;
public:
    Cab();
    int getMeterPassed();
    int getTariff();
    int getID();
    int canMove();

    void addMeter(int meter);

};

#endif //EX2_CAB_H
// cab