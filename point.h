/**
 * Amos Maimon And Or Zipori.
 *
 * Point Header.
 */

#ifndef EX1_POINT_H
#define EX1_POINT_H

#include <iostream>
#include "Key.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>

#include <fstream>
#include <sstream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>


/**
 * Point class.
 *
 * Describes a single point in space.
 */
using namespace boost::archive;
class Point : Key{
private:
    int x;
    int y;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version){
        archive & x;
        archive & y;

    }
public:
    Point(int nX, int nY);
    Point(){}
    int getX() const;
    int getY() const ;
    friend std::ostream& operator<< (std::ostream& stream, const Point& p);
    bool operator==(Point const& p) const ;


private:
    void implemented(){};
};


#endif //EX1_POINT_H
