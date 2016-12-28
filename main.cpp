#include <iostream>
#include <queue>
#include "point.h"
#include "StringParser.h"
#include "MainFlowClass.h"
#include "Client.h"
#include "Server.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>

using namespace std;

void save(Driver d)
{
    std::ofstream file("kokomiao.xml");
   // boost::archive::xml_oarchive oa(file);
    //oa & BOOST_SERIALIZATION_NVP(d);
    file.close();
}


/**
 * Main  of the program.
 *
 * @return 0
 */
int main(int argc,char *argv[]) {
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

    if (atoi(argv[1]) == 1) {
        Client client = Client();
        return client.run();
    } else if (atoi(argv[1]) == 2) {
        Server server = Server();
        return server.run();
    } else {
        cout << "no args input ..." << endl;
    }



    delete(s);
    return 0;
}
