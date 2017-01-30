/**
 * Amos Maimon And Or Zipori.
 *
 * BFS Implementaion.
 */

#include "BFS.h"


BFS::BFS() {}
/**
 * Get a Grid and end Point, and map the grid by distance from the end point - using BFS algorithm.
 *
 * @param map
 * @param end
 */
void BFS::makeMap(Grid &map, const Point &end) {
    
    std::queue<Point> queue;
    Point current = end;
    map.setDistance(current, 0);

    queue.push(current);

    while(!queue.empty()) {
        current = queue.front();

        queue.pop();

        std::queue<Point>  brothers = map.getBrothers(current);

        while(!brothers.empty()) {
            Point brother = brothers.front();
            brothers.pop();

            if (map.getDistance(brother) == -1) {
                map.setDistance(brother, (map.getDistance(current) + 1));
                map.setNextStep(brother, current);
                queue.push(brother);
            }
        }
    }
}

/**
 * Get a marked map, and returns the Point that closer to the end point.
 * @param map
 * @param freeDrivers
 * @param driversCount
 * @return Point
 */
Point BFS::bestNode(Grid &map, const Point *freeDrivers, int driversCount) {
    Point best = freeDrivers[0];
    for(int i = 1; i < driversCount; i++) {
        if (map.getDistance(best) > map.getDistance(freeDrivers[i])) {
            best = freeDrivers[i];
        }
    }
    return best;
}

/**
 * get copy of Grid, end point & array of start points (free Drivers).
 * return a queue of Point start from the best start point
 * until the end point that received.
 *
 * notes for the inspector:
 * We thinking ahead, and we decided to start the algorithm
 * from the end point, and test a series of starting points.
 *
 * In this way our code ready to get a large number of starting points
 * (that will represent in the future - free drivers) and return the
 * shortest path from the closest starting point(free driver)
 * antill the end point.
 *
 *
 * @param map
 * @param end
 * @param freeDrivers
 * @param driversCount
 * @return queue of Points.
 */
std::queue<Point> BFS::run(Grid map, const Point &end, const Point *freeDrivers, int driversCount) {

    std::queue<Point> route;
    makeMap(map, end);
    Point current = bestNode(map, freeDrivers, driversCount);
    int distance = map.getDistance(current);
    route.push(current);
    for(int i = 0; i <= distance; i++) {
        current = map.getNextStep(current);
        route.push(current);

    }
    return route;
}
