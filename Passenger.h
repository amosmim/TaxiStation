/**
 * Amos Maimon And Or Zipori.
 *
 * Passenger Header.
 */

#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

/**
 * Passenger Class.
 *
 * Represents the passengers that requires trips over the grid.
 */

#include "point.h"
#include <stdlib.h>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
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
#include <sstream>

class Passenger {
private:
    Point startPoint;
    Point endPoint;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive & startPoint;
        archive & endPoint;
    }
public:
    Passenger(Point s, Point e);
    Passenger(){}
    Point getStartPoint();
    Point getEndPoint();
    int generateScore();
};


#endif //EX2_PASSENGER_H
