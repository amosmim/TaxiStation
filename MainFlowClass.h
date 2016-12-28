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

using namespace std;

class MainFlowClass{
private:

    TaxiCenter *taxiCenter;
    Grid *grid;
    Statistics *stats;

    void moveOneStep();

public:
    MainFlowClass();
    void createNewDriver(int id, int age, Status s, int exp, int v_id);
    void createNewCab(int id,  CabType t, CarType c, CarColor co, int tariff);
    void createNewTripInfo(int id, Point start, Point end, vector<Passenger> p, int tariff);
    void createTaxiStation();
    vector<string> getUserInput(string toParsed);
    void run(int mainKey, string toParsed);
    void setGrid(int x, int y, vector<Point> obstacles);
    ~MainFlowClass();
};

#endif //EX2_MAINFLOWCLASS_H
