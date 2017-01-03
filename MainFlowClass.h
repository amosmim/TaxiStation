/**
 * Amos Maimon And Or Zipori.
 *
 * MainFlowClass Header.
 */

#ifndef EX2_MAINFLOWCLASS_H
#define EX2_MAINFLOWCLASS_H

/**
 * MainFlowClass Class.
 *
 * This class is in charge of the main logic of the game.
 */

#include "Status.h"
#include "CarType.h"
#include "CarColor.h"
#include "point.h"
#include "Passenger.h"
#include "TaxiCenter.h"
#include "grid.h"
#include "CabType.h"
#include <vector>
#include <string>
#include <iostream>
#include "StringParser.h"
#include "StandardCab.h"
#include <limits>

#define PORT_NUM 46287
#define CONNECTION_TYPE 'U' // == UDP mark
using namespace std;

class MainFlowClass{
private:

    TaxiCenter *taxiCenter;
    Grid *grid;
    //Statistics *stats;



public:
    MainFlowClass();
    void createNewDriver();
    void createNewCab(int id,  CabType t, CarType c, CarColor co, int tariff);
    void createNewTripInfo(int id, Point start, Point end, vector<Passenger> p, int tariff, int onTime);
    void createTaxiStation();
    vector<string> getUserInput();
    void run();
    void setGrid(int x, int y, vector<Point> obstacles);
    ~MainFlowClass();
};

#endif //EX2_MAINFLOWCLASS_H
