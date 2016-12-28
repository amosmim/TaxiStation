/**
 * Amos Maimon And Or Zipori.
 *
 * Node Implementaion.
 */

#include "Node.h"

/**
 * Defult Constructor.
 *
 */
Node::Node()  {
    nextNodeStep = Point(-1,-1);
    location = &nextNodeStep;
    isTaken = false;
    distance = -1;
}

/**
 * Constructor.
 *
 * @param loc Point.
 *
 */
Node::Node(Point *loc){
    location = loc;
    nextNodeStep = *loc;
    isTaken = false;
    distance = -1;
}



/**
 * Set distance.
 * @param d distance
 */
void Node::setDistance(int d) {
    distance = d;
}

/**
 * Return distance.
 * @return distance
 */
int Node::getDistance() {
    return distance;
}

/**
 * notes for the inspector:
 * 'isTaken' getter and setter will be used when obstacles and
 * other vehicles will add to the program.
 */

 /**
 * Set isTaken.
 * @param taken
 */
void Node::setTaken(bool taken) {
    isTaken = taken;
}

/**
 * Get isTaken.
 * @return bool.
 */
bool Node::getTaken() {
    return isTaken;
}

/**
 * Get location.
 * @return point
 */
Point* Node::getLocation() {

    return location;
}


/**
 * Set the next step.
 * @param point
 */
void Node::setNextStep(Point next) {
    nextNodeStep = next;
}

/**
 * Get the next point to move to.
 *
 * @return Point.
 */
Point& Node::getNextStep() {
    return nextNodeStep;
}

/**
 * Operator overloading for <<
 *
 * @param stream
 * @param node
 * @return stream
 */
std::ostream& operator<< (std::ostream& stream, const Node& node) {
    stream << node.getPoint();
    return stream;
}


/**
 * set the Point to this node location
 * @param point
 */
void Node::setLocation(Point* point) {
    location = point;
}

/**
 * Const Version to getLocation() for stream conversion.
 * @return const Point
 */
const Point *Node::getPoint() const {
    return location;
}

Node::~Node() {
    /*
    if(location) {
        std::cout << "deleting " << *location << std::endl;
        delete location;
        std::cout << "succeeded" << std::endl;
    }*/
}