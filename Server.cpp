//
// Created by amos on 12/28/16.
//

#include "Server.h"
int main(int argc,char *argv[]) {

    string input;
    string tamp;
    MainFlowClass mainFlow;
    int gridX, gridY;

    // Get x and y for grid
    getline(cin, input);

    StringParser sp(input);
    vector<string> parsed = sp.split(' ');

    gridX = atoi(parsed[0].c_str());
    gridY = atoi(parsed[1].c_str());

    // Get obstacles number
    getline(cin, input);

    int obstacles = atoi(input.c_str());
    vector<Point> obstaclesList;
    // Create obstacles list if necessary
    while (obstacles != 0) {
        getline(cin, input);
        sp.setStr(input);
        parsed = sp.split(',');
        int x = atoi(parsed[0].c_str());
        int y = atoi(parsed[1].c_str());
        obstaclesList.push_back(Point(x, y));
        obstacles--;
    }
    int port = 0;
    // get port number from commend line
    if (argc > 1){
        port = atoi(argv[1]);
    }
    mainFlow.setGrid(gridX, gridY, obstaclesList);
    mainFlow.createTaxiStation(port, CONNECTION_TYPE);
    mainFlow.run();
    return 0;
}
