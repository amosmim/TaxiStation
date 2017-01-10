/**
 * Amos Maimon And Or Zipori.
 *
 * MainFlowClass Implementation.
 */


#include "MainFlowClass.h"

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


    //delete(stats);
}

/**
 * Create a new driver and add him/her to the taxi center.
 */
void MainFlowClass::createNewDriver() {
    //Driver* driver = new Driver(id,age,s, exp, v_id);
    //taxiCenter->addNewDriver(driver);
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
    //taxiCenter.setTripInfo(id,);
    TripInfo *t =  new TripInfo(id, start, end, p, tariff, onTime);
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
    //cin >> input;
    sp.setStr(input);
    return sp.split(',');
}

/**
 * Main GUI.
 * In charge of creating drivers, cabs, trips and answer the current location query.
 * Also, initiate the task to drive.
 */
void MainFlowClass::run() {
    vector<string> parsed;

    // Menu
    int mainKey;
    do {
        cin >> mainKey;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (mainKey) {
            case 1: // Enter a new driver
            {
                /*
                parsed = getUserInput();
                int id = atoi(parsed[0].c_str());
                int age = atoi(parsed[1].c_str());
                char status = parsed[2].at(0);
                int exp = atoi(parsed[3].c_str());
                int v_id = atoi(parsed[4].c_str());
                Status st;

                switch (status) {
                    case 'S':
                        st = Status::SINGLE;
                        break;
                    case 'D':
                        st = Status::DIVORCED;
                        break;
                    case 'W':
                        st = Status::WIDOWED;
                        break;
                    case 'M':
                        st = Status::MARRIED;
                        break;
                }*/
                int driversNum;
                cin >> driversNum;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for (int i = 0; i < driversNum;++i) {
                    createNewDriver();
                }
                break;
            }
            case 2: // Add new ride
            {
                parsed = getUserInput();
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

                break;
            }
            case 3: // Add a new cab
            {
                parsed = getUserInput();
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
            }
                break;
            case 4: {
                int driverID;

                // Get the id of the driver
                cin >> driverID;
                // Print the point
                cout << taxiCenter->getDriverLocation(driverID) << endl;
            }
                break;


            case 9:{
                taxiCenter->moveOneStep(); }
                break;
        }
    }
    while (mainKey != 7);

}
