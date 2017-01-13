/**
 * Amos Maimon And Or Zipori.
 *
 * Grid Implementaion.
 */


#include "grid.h"

/**
 * Constructor.
 *
 * @param x size on x axis
 * @param y size on y axis
 *
 */
Grid::Grid(int x, int y) {
    size = Point(x, y);

    // Declare two dimensional array
    // basically array of arrays
    map = new Node*[x];
    for(int i = 0; i < x; ++i) {
        map[i] = new Node[y];
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            map[i][j] = Node(new Point(i,j));
        }
    }
}

/**
 * Destructor
 */
Grid::~Grid() {

    int x = size.getX();
    int y = size.getY();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Point *del = map[i][j].getLocation();
            delete del;
        }
    }

    // Free the two dimensional array
    for (int i = 0; i < x; ++i) {
        delete[] map[i];
    }
    delete [] map;
}

/**
 * Copy Constractor
 */
Grid::Grid(const Grid& g) {

    size = g.getBoundaries();

    int x = size.getX();
    int y = size.getY();

    map = new Node*[x];
    for(int i = 0; i < x; ++i) {
        map[i] = new Node[y];
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {

            map[i][j] = g.getNode(i, j);
            map[i][j].setLocation(new Point(i,j));
        }
    }

}

/**
 * Get the boundaries of the grid.
 *
 * @return Point
 */
Point Grid::getBoundaries() const{
    return size;
}

/**
 * This function is in charge of getting a Point and returning it's brothers,
 * according to the instructed directions.
 *
 * @param current
 * @return vector of Points.
 */
std::queue<Point>  Grid::getBrothers(Point current) {
    std::queue<Point> brothers;

    int x = current.getX();
    int y = current.getY();

    // checking 9 o'clock
    if (x - 1 >= 0) {
        brothers.push(Point(x-1, y));
    }
    // checking 12 o'clock
    if (y + 1 <= size.getY() - 1) {
        brothers.push(Point(x, y + 1));
    }
    // checking 15 o'clock
    if (x + 1 <= size.getX() - 1) {
        brothers.push(Point(x+1, y));
    }
    // checking 18 o'clock
    if (y - 1 >= 0) {
        brothers.push(Point(x, y-1));
    }
    return brothers;
}

/**
 * Set distance to a Node in the grid.
 *
 * @param location
 * @param distance
 */
void Grid::setDistance(const Point &location, int distance) {
    int x = location.getX();
    int y = location.getY();
    map[x][y].setDistance(distance);
}

/**
 * Get the distance of a Node in the grid.
 * @param location
 * @return distance of a Node in the grid.
 */
int Grid::getDistance(const Point &location) {
    int x = location.getX();
    int y = location.getY();
    return map[x][y].getDistance();
}

/**
 * Set the next point to step inside a choosen Node.
 * @param location
 * @param nextStep
 */
void Grid::setNextStep(const Point &location, const Point &nextStep) {
    int x = location.getX();
    int y = location.getY();
    map[x][y].setNextStep(nextStep);
}

/**
 * Get the next point to step inside a choosen Node.
 * @param location
 */
Point& Grid::getNextStep(const Point &location) {
    int x = location.getX();
    int y = location.getY();
    return map[x][y].getNextStep();
}

/**
 * Version for inheritance to getBrothers()
 * @param current
 * @return queue<Key>
 */
std::queue<Key> &Grid::getBrothers(Key &current) {
    return getBrothers( current);
}

/**
 * Version for inheritance to setDistance()
 * @param location Key
 * @param distance int
 */
void Grid::setDistance(const Key &location, int distance) {
    Point point= (Point&)location;
    setDistance(point, distance);
}

/**
 * Version for inheritance to getDistance()
 * @param location
 * @return int
 */
int Grid::getDistance(const Key &location) {
    Point point= (Point&)location;
    return getDistance(point);
}

/**
 * Version for inheritance to setNextStep()
 * @param location Key
 * @param nextStep Key
 */
void Grid::setNextStep(const Key &location, const Key &nextStep) {
    Point point= (Point&)location;
    Point point2= (Point&)nextStep;
    setNextStep(point, point2);
}

/**
 * Version for inheritance to getNextStep()
 * @param location
 * @return key
 */
Key &Grid::getNextStep(const Key &location) {
    const Point point= (Point&)location;
    return (Key&)getNextStep(point);
}

/**
 * Returns the Node in (i,j)
 * @param i
 * @param j
 * @return Node
 */
Node Grid::getNode(int i, int j) const{
    return map[i][j];
}
