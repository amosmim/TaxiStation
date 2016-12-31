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
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class MainFlowClass{
private:

    TaxiCenter *taxiCenter;
    Grid *grid;
    Statistics *stats;
    struct sockaddr_in *from;

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
    Cab& getCabFor(int id);
    ~MainFlowClass();
    void setSock(struct sockaddr_in* from);

    sockaddr_in *getFrom();
};

#endif //EX2_MAINFLOWCLASS_H
