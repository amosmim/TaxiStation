/**
 * Amos Maimon And Or Zipori.
 *
 * Grid Header.
 */

#ifndef EX1_GRID_H
#define EX1_GRID_H


#include <cstdlib>
#include "point.h"
#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <queue>

/**
 * Grid class.
 *
 * Describes the world (map).
 */

class Grid : Graph{
private:
    //Node map[10][10];
    Node **map;
    Point size;
public:
    Grid(){};
    Grid(int x, int y);
    ~Grid();
    Grid(const Grid& g);
    Point getBoundaries() const;
    std::queue<Point> getBrothers(Point current);
    void setDistance(const Point &location, int distance);
    int getDistance(const Point &location);
    void setNextStep(const Point &location, const Point &nextStep);
    Point& getNextStep(const Point &location);

private:
    Node getNode(int i, int j) const;
    virtual std::queue<Key> &getBrothers(Key &current);

    virtual void setDistance(const Key &location, int distance);

    virtual int getDistance(const Key &location);

    virtual void setNextStep(const Key &location, const Key &nextStep);

    virtual Key &getNextStep(const Key &location);
};

#endif //EX1_GRID_H
