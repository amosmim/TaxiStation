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
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/ref.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/export.hpp>
#include <sstream>

class LuxuryCab : public Cab {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & boost::serialization::base_object<Cab>(*this);
    }

public:
    LuxuryCab (int id, CarType t, CarColor c, int tariff);
    LuxuryCab () {}
    int canMove();

};


#endif //EX2_LUXURYCAB_H
