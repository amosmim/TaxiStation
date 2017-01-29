/**
 * Amos Maimon And Or Zipori.
 *
 * MainFlowClass Implementation.
 */


#include "MainFlowClass.h"
#include "easylogging++.h"

/**
 * Constructor.
 * @return object
 */
MainFlowClass::MainFlowClass() {
    // set default port number.
    port = 46287;
}

/**
 * Set the grid for the game.
 * @param x grid x size
 * @param y grid y size
 * @param obstacles vector<Point>
 */
void MainFlowClass::setGrid(int x, int y, std::vector<Point> obstacles) {
    grid = new Grid(x, y);
    Point tamp;
    this->obstscales = obstacles;
    while(!obstacles.empty()) {
        tamp = obstacles.back();
        obstacles.pop_back();
        // set the distance field to zero to mark the its cannot step in BFS algorithm.
        grid->setDistance(tamp, 0);
    }
}

/**
 * Destructor.
 */
MainFlowClass::~MainFlowClass() {
	delete(grid);
	delete(taxiCenter);

}

/**
 * Create a new driver and add him/her to the taxi center.
 */
void MainFlowClass::createNewDriver() {

    taxiCenter->addNewDriver();
}

/**
 * Create a new cab and add it to the taxi center.
 * @param id id number
 * @param t CabType
 * @param c CarType
 * @param co CarColor
 * @param tariff
 */
void MainFlowClass::createNewCab(int id, CabType t, CarType c, CarColor co, int tariff) {
    Cab *cab;

    if (t == CabType::LUXURY) {
        cab = new LuxuryCab(id, c, co, 2);
    } else {
        cab = new StandardCab(id, c, co, 1);
    }

    taxiCenter->addNewCab(cab);
}

/**
 * Create a new TripInfo and add it to the order's queue in the taxi center.
 * @param id id number
 * @param start point
 * @param end point
 * @param p vector <Passenger>
 * @param tariff
 */
void MainFlowClass::createNewTripInfo(int id, Point start, Point end, vector <Passenger> p, int tariff , int onTime) {

    TripInfo *t =  new TripInfo(id, start, end, p, tariff, onTime);

    // Get the inner thread
    pthread_t currentThread = t->getThread();
    // Assign the data to the DataTypeClass == function arguments
    DataTypeClass *dtc = new DataTypeClass();
    dtc->g = grid;
    dtc->trip = t;
    if (pthread_create(&(t->BFSthread), NULL, runBFS, (void*) dtc)) {
        perror("Error");
    }

    taxiCenter->receiveOrder(t);
}

/**
 * Create a taxi center.
 */
void MainFlowClass::createTaxiStation(int newPort, char connectionType) {
    if ((newPort > 1023)&&(newPort < 49152)) {
        port = newPort;
    }
    taxiCenter = new TaxiCenter(grid);
    taxiCenter->setSocket(port, connectionType);
}

/**
 * Get the user input and parse it.
 * @return Parsed vector
 */
vector<string> MainFlowClass::getUserInput() {
    string input;
    StringParser sp;

    getline(cin, input);

    sp.setStr(input);
    return sp.split(',');
}

/**
 * The function which the thread runs in order to calculate the directions.
 *
 * @param args
 * @return
 */
void* MainFlowClass::runBFS(void *args) {
    BFS calculator;
    TripInfo *trip;
    Grid *map;
    DataTypeClass *dtc = (DataTypeClass *) args;

    // Load arguments to the correct types
    trip = dtc->trip;
    map = dtc->g;

    Point start = trip->getStartPoint();
    trip->setDirections(calculator.run(*map, trip->getEndPoint(), &start, 1));

    delete(dtc);
}

/**
 * Main GUI.
 * In charge of creating drivers, cabs, trips and answer the current location query.
 * Also, initiate the task to drive.
 */
void MainFlowClass::run() {
    vector<string> parsed;
    int gridX, gridY;

    gridX = grid->getBoundaries().getX();
    gridY = grid->getBoundaries().getY();

    StringParser sp;

    LOG(INFO) << "Menu start";
    // Menu
    int mainKey;
    do {
        cin >> mainKey;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (mainKey) {
            case 1: // Enter a new driver
            {
                int driversNum;
                cin >> driversNum;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                for (int i = 0; i < driversNum;++i) {
                    taxiCenter->addNewDriver();

                }
                taxiCenter->waitForThreads();
                LOG(INFO) << "End of receiving " << driversNum << " clients";
                break;
            }
            case 2: // Add new ride
            {
                parsed = getUserInput();

                // Input verification
                if (!sp.missionInputVerification(parsed, 2, gridX, gridY, this->obstscales)) {
                    // Ignore input
                    break;
                }

                int rid = atoi(parsed[0].c_str());
                int x_start = atoi(parsed[1].c_str());
                int y_start = atoi(parsed[2].c_str());
                int x_end = atoi(parsed[3].c_str());
                int y_end = atoi(parsed[4].c_str());
                int numPassengers = atoi(parsed[5].c_str());
                double tariff = atoi(parsed[6].c_str());
                int onTime = atoi(parsed[7].c_str());

                // Create passengers
                vector<Passenger> passengers;
                Point start(x_start, y_start);
                Point end(x_end, y_end);
                while (numPassengers != 0) {
                    passengers.push_back(Passenger(start, end));
                    numPassengers--;
                }
                createNewTripInfo(rid, start, end, passengers, tariff, onTime);
                LOG(INFO) << "Trip number " << rid << " created.";

                break;
            }
            case 3: // Add a new cab
            {
                parsed = getUserInput();

                // Input verification
                if (!sp.missionInputVerification(parsed, 3, gridX, gridY, this->obstscales)) {
                    // Ignore input
                    break;
                }

                int cid = atoi(parsed[0].c_str());
                int cabType = atoi(parsed[1].c_str());
                char type = parsed[2].at(0);
                char color = parsed[3].at(0);
                CarType ct;
                CarColor cc;

                switch (type) {
                    case 'H':
                        ct = CarType::HONDA;
                        break;
                    case 'S':
                        ct = CarType::SUBARU;
                        break;
                    case 'T':
                        ct = CarType::TESLA;
                        break;
                    case 'F':
                        ct = CarType::FIAT;
                        break;
                    default:
                        perror("con't find Car Type = " + type);
                }

                switch (color) {
                    case 'R':
                        cc = CarColor::RED;
                        break;
                    case 'G':
                        cc = CarColor::GREEN;
                        break;
                    case 'W':
                        cc = CarColor::WHITE;
                        break;
                    case 'P':
                        cc = CarColor::PINK;
                        break;
                    case 'B':
                        cc = CarColor::BLUE;
                        break;
                    default:
                        perror("con't find Color Type = " + color);
                }

                if (cabType == 1) {
                    createNewCab(cid, CabType::STANDARD, ct, cc, 1);
                } else {
                    createNewCab(cid, CabType::LUXURY, ct, cc, 2);
                }

                LOG(INFO) << "Cab " << cid << " created.";
            }
                break;
            case 4: {
                int driverID;

                // Get the id of the driver
                cin >> driverID;
                // Print the point
                Point p = taxiCenter->driverLocation(driverID);
                // Only if driver id exists, else ignore command
                if (p.getX() != -1) {
                    cout << p << endl;
                } else {
                    cout << "-1\n";
                }
                LOG(INFO) << "Driver " << driverID << " At " << p;
            }
                break;
            case 7: {
                break;
            }

            case 9:{
                LOG(INFO) << "Move one step.";
                taxiCenter->moveOneStep();
            }
                break;
            default: { // Bad mission id
                cout << "-1\n";
            }
        }
    }
    while (mainKey != 7);

}
