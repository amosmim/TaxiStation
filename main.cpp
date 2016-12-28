#include <iostream>
#include <queue>
#include "point.h"
#include "StringParser.h"
#include "MainFlowClass.h"
#include <fstream>

using namespace std;

void save(Driver d)
{
    std::ofstream file("kokomiao.xml");
    boost::archive::xml_oarchive oa(file);
    oa & BOOST_SERIALIZATION_NVP(d);
}


/**
 * Main  of the program.
 *
 * @return 0
 */
int main() {
    // main driver statistics taxicenter trip
    /*
    MainFlowClass mainFlow;
    int gridX, gridY;
    string input;
    // Get x and y for grid
    getline(cin, input);

    StringParser sp(input);
    vector<string> parsed = sp.split(' ');

    gridX = atoi(parsed[0].c_str());
    gridY = atoi(parsed[1].c_str());

    // Get obstcales number
    getline(cin, input);

    int obstcales = atoi(input.c_str());
    vector<Point> obstaclesList;
    // Create obstacles list if necessary
    while (obstcales != 0) {
        getline(cin, input);
        sp.setStr(input);
        parsed = sp.split(',');
        int x = atoi(parsed[0].c_str());
        int y = atoi(parsed[1].c_str());
        obstaclesList.push_back(Point(x, y));
        obstcales--;
    }

    mainFlow.setGrid(gridX, gridY, obstaclesList);
    mainFlow.createTaxiStation();
    // all the other input will input there
    mainFlow.run();

    return 0; */
    Statistics *s = new Statistics();
    Driver d(2,2,Status::MARRIED,2, 2, s);
    save(d);


    delete(s);
    return 0;
}
