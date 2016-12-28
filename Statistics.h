/**
 * Amos Maimon And Or Zipori.
 *
 * Statistics Header.
 */

#ifndef EX2_STATISTICS_H
#define EX2_STATISTICS_H


#include <map>
#include "point.h"

class Statistics {
private:
    std::map<int, Point> dataSet;
public:
    Statistics();
    void setData(int id, Point place);
    Point getLocationByID(int id);
};


#endif //EX2_STATISTICS_H
