/**
 * Amos Maimon And Or Zipori.
 *
 * Point Implementaion.
 */

#include "point.h"

/**
 * Constructor.
 *
 * @param x location on x axis
 * @param y location on y axis
 *
 */
Point::Point(int nX, int nY) {
    x = nX;
    y = nY;
}


/**
 * destructor.
 *
 */

/**
 * @return location on x axis.
 */
int Point::getX() const {
    return x;
}

/**
 * @return location on y axis
 */
int Point::getY() const {
    return y;
}

/**
 * print the Point on stream.
 * @param stream to print on.
 * @param p point to print.
 * @return print the Point on stream with the '<<' operator.
 */
std::ostream& operator<< (std::ostream& stream, const Point& p) {
    stream << "(" << p.getX() << "," << p.getY() << ")";
    return stream;
}

/**
 * equal operator
 * @param p point to compare
 * @return true if there value are equals.
 */
bool Point::operator==(Point const& p) const{
    return ((x == p.getX()) && (y == p.getY()));
}
