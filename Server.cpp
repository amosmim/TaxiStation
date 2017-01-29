/**
 * Amos Maimon And Or Zipori.
 *
 */

#include "Server.h"
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc,char *argv[]) {

    string input;
    string tamp;
    MainFlowClass mainFlow;
    int gridX, gridY;
    bool varification = false;
    int stages = 0;
    int obstacles;
    vector<Point> obstaclesList;
    StringParser sp;
    vector<string> parsed;

    LOG(INFO) << "Server started";

    while (!varification) {
        switch(stages) {
            case 0: { // stage 0 == getting correct map size
                // Get x and y for grid
                getline(cin, input);
                sp.setStr(input);

                parsed = sp.split(' ');

                // Either the delimiter was not ' ' or more/less than 2 coordinates
                if (parsed.size() != 2) {
                    cout << "-1\n";
                    stages = 0;
                } else {
                    // If numbers where given and not chars
                    if (sp.isInt(parsed[0]) && sp.isInt(parsed[1]))
                    {
                        gridX = atoi(parsed[0].c_str());
                        gridY = atoi(parsed[1].c_str());
                        if (gridX > 0 && gridY > 0){
                            stages++; // On to the next stage
                        } else {
                            cout << "-1\n";
                            stages = 0;
                        }
                    } else { // not integers
                        cout << "-1\n";
                    }
                }
                break;
            }
            case 1: { // stage 1 == get obstacles
                // Get obstacles number
                getline(cin, input);

                // Command so no white space allowed
                if (sp.isInt(input)) {
                    obstacles = atoi(input.c_str());
                    if (obstacles < 0) { // if number of obstacles is less than 0
                        cout << "-1\n";
                        stages = 0;
                        break;
                    }
                } else {
                    cout << "-1\n";
                    stages = 0;
                    break;
                }

                // No need to continue if there are no obstacles
                if (obstacles == 0){
                    stages++;
                    break;
                }

                // Create obstacles list if necessary
                while (obstacles != 0) {
                    getline(cin, input);
                    sp.setStr(input);
                    parsed = sp.split(',');

                    if (parsed.size() != 2) {
                        cout << "-1\n";
                        stages = 0;
                        break;
                    }

                    // Check if point coordinates are integers
                    if (sp.isInt(parsed[0]) && sp.isInt(parsed[1])) {
                        int x = atoi(parsed[0].c_str());
                        int y = atoi(parsed[1].c_str());
                        // Check if the point is on the map
                        if (sp.isLegitPoint(x, y, gridX, gridY)) {
                            obstaclesList.push_back(Point(x, y));
                            obstacles--;
                        } else { // Point is not on the map
                            cout << "-1\n";
                            stages = 0;
                            break;
                        }
                    } else { // x and y are not integers
                        cout << "-1\n";
                        stages = 0;
                        break;
                    }
                    stages++;
                }
            }
            break;
        }
        // Input check is over
        if (stages >= 2) {
            varification = true;
        }
    }

    // If input is correct
    int port = 0;
    // get port number from commend line
    if (argc > 1){
        port = atoi(argv[1]);
    }
    mainFlow.setGrid(gridX, gridY, obstaclesList);
    mainFlow.createTaxiStation(port, CONNECTION_TYPE);
    mainFlow.run();

    LOG(INFO) << "Server ended.";
    return 0;
}
