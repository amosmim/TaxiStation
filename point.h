/**
 * Amos Maimon And Or Zipori.
 *
 * Point Header.
 */

#ifndef EX1_POINT_H
#define EX1_POINT_H

#include <iostream>
#include "Key.h"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

/**
 * Point class.
 *
 * Describes a single point in space.
 */

class Point : Key{
private:
    int x;
    int y;

public:
    Point(int nX, int nY);
    Point(){}
    int getX() const;
    int getY() const ;
    friend std::ostream& operator<< (std::ostream& stream, const Point& p);
    bool operator==(Point const& p) const ;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version);

private:
    void implemented(){};
};


#endif //EX1_POINT_H
