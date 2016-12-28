/**
 * Amos Maimon And Or Zipori.
 *
 * BFS Header.
 */

#ifndef EX1_BFS_H
#define EX1_BFS_H

#include "point.h"
#include "grid.h"
#include "Node.h"

#include <queue>

class BFS {
private:
    // get a Grid and end Point, and map the grid by distance from the end point - using BFS algorithm.
    void makeMap(Grid &map, const Point &end);
    // get a marked map, and returns the Point that closer to the end point.
    Point bestNode(Grid &map, const Point *freeDrivers, int driversCount);
public:
    BFS();
    // get a copy(!) of the grid, and find the best route.
    std::queue<Point> run(Grid map, const Point &end, const Point *freeDrivers, int driversCount);


};

#endif //EX1_BFS_H