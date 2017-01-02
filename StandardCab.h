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
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/ref.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/export.hpp>
#include <sstream>

class StandardCab : public Cab {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & boost::serialization::base_object<Cab>(*this);
    }

public:
    StandardCab (int id, CarType t, CarColor c, int tariff);
    StandardCab() {}
    int canMove();
};



#endif //EX2_STANDARDCAB_H
