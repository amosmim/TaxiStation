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
#include <pthread.h>


using namespace std;

class MainFlowClass{
private:
    int port;
    TaxiCenter *taxiCenter;
    Grid *grid;

    //Statistics *stats;



public:
    MainFlowClass();
    void createNewDriver();
    void createNewCab(int id,  CabType t, CarType c, CarColor co, int tariff);
    void createNewTripInfo(int id, Point start, Point end, vector<Passenger> p, int tariff, int onTime);
    void createTaxiStation(int newPort, char connectionType);
    vector<string> getUserInput();
    static void* runBFS(void *args);
    void run();
    void setGrid(int x, int y, vector<Point> obstacles);
    ~MainFlowClass();
};

#endif //EX2_MAINFLOWCLASS_H
