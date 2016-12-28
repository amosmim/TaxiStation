/**
 * Amos Maimon And Or Zipori.
 *
 * Node Header.
 */

#ifndef EX1_NODE_H
#define EX1_NODE_H

#include "point.h"
#include <iostream>

/**
 * Node class.
 *
 * Describes a single node in the grid.
 */

class Node {
private:
    Point* location;
    int distance;
    bool isTaken;
    Point nextNodeStep;
    const Point *getPoint() const;

public:
    Node();
    Node(Point *loc);
    void setDistance(int d);
    int getDistance();
    void setTaken(bool taken);
    bool getTaken();
    Point *getLocation() ;
    void setLocation(Point *point);
    void setNextStep(Point next);
    Point& getNextStep();
    friend std::ostream& operator<< (std::ostream& stream, const Node& node);
    ~Node();
};


#endif //EX1_NODE_H
