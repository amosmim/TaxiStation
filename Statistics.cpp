/**
 * Amos Maimon And Or Zipori.
 *
 * Statistics Implementation.
 */

#include "Statistics.h"
/**
 * Constructor.
 */
Statistics::Statistics() {

}
/**
 * change driver location.
 * @param id driver ID
 * @param place current point
 */
void Statistics::setData(int id, Point place) {
    dataSet[id] = place;
}

/**
 * get driver location
 * @param id driver ID
 * @return current point
 */
Point Statistics::getLocationByID(int id) {
    return dataSet[id];
}
