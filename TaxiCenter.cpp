/**
 * Amos Maimon And Or Zipori.
 *
 * TaxiCenter Implementation.
 */


#include "TaxiCenter.h"
#include "DataTypeClass.h"

/**
 * Constructor.
 * @param grid
 * @return
 */
TaxiCenter::TaxiCenter(Grid* grid) {
    map = grid;
    timeCounter = 0;
    //driversID = new std::map<int,int>();
}

/**
 * Receive the order from the client and set the direction.
 *
 * @param t
 */
void TaxiCenter::receiveOrder(TripInfo *t) {
    Point start = t->getStartPoint();
    t->setDirections(calculator.run(*map, t->getEndPoint(), &start, 1));
    tripsList.push_back(t);
}

/**
 * Add a new driver to the station.
 * @param d
 * @param  descriptor of the driver
 */
void TaxiCenter::addNewDriver() {
    int descriptor = this->socket->acceptOneClient();
    if (descriptor<=0){
        perror("addNewDriver - crush No. 1");
        exit(1);
    }

    // SHOULD BE THREADED HERE :
    driverData *dB = new driverData;
    dB->driversDescriptors = descriptor;
    this->driversDescriptors.push_back(descriptor);
    char buffer[10];
    // receive driver ID
    int work = socket->receiveData(buffer, 10, descriptor);
    int driverID = atoi(buffer);

    driversID[descriptor]=driverID;
    dB->driverID = driverID;

    dB->location = Point(0, 0);
    dataMap[descriptor] = dB;

    // send cab serialized
    for (int j = 0; j < cabsList.size(); j++) {
        if (cabsList[j]->getID() == driverID) {
            //char buffer2[1000];
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);

            Cab *c = cabsList[j];
            oa << c;
            s.flush();

            socket->sendData(serial_str,dB->driversDescriptors);
            char buffer3[100];
            socket->receiveData(buffer3, 100, dB->driversDescriptors);
            //string config = buffer3;
            if (atoi(buffer3) != cabsList[j]->getID()) {
                perror("connection error - addDriver - Cab" + driverID);
            }
            // delete the cab from list
            delete(c);
            cabsList.erase(cabsList.begin() + j);
            break;
        }
    }
}

/**
 * Assign a single trip to the correct driver. Thread Function.
 * @param data
 * @return
 */
void *TaxiCenter::doOneStepThreaded(void *data) {
    // Assign trip to driver
    DataTypeClass *dB = (DataTypeClass *) data;

    pthread_mutex_t list_locker;

    TaxiCenter *taxiCenter = dB->server;
    int timeCounter  = dB->timeCounter;
    driverData *driverData = dB->data;
    Socket *serverSocket =  dB->socket;
    int descriptor = dB->data->driversDescriptors;

    cout << "\n Thread Started " << driverData->driverID;

    // If there is not current trip to send
    if (dB->trip == NULL) {
        // Send and receive - preform the move one step
        serverSocket->sendData(DRIVE, driverData->driversDescriptors);

        // Double check - if the client received
        char buffer[100];
        serverSocket->receiveData(buffer, 100, driverData->driversDescriptors);

        cout << "\n First Send " << driverData->driverID;
    } else {
        // serialized tripInfo
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);

        oa << dB->trip;
        s.flush();
        // send tripinfo to client
        serverSocket->sendData(GET_TRIPINFO, descriptor);
        char buffer[100];
        serverSocket->receiveData(buffer,100, descriptor);
        if(buffer[0] != GET_TRIPINFO[0]){
            perror("Connection Error - TripInfo send from TaxiCenter");
        }
        // Send serialized tripInfo
        serverSocket->sendData(serial_str,descriptor);
        //socket->receiveData(buffer,100,descriptor);

        char buffer2[100];
        serverSocket->receiveData(buffer2,100, descriptor);

        cout << "\n Trip Sent " << driverData->driverID;
    }

    //pthread_mutex_lock(&list_locker);
    driverData->location = taxiCenter->getDriverLocation(driverData->driverID);
    //pthread_mutex_unlock(&list_locker);

    cout << "\n Thread Ended " << driverData->driverID;

    delete(data);
    pthread_mutex_destroy(&list_locker);
}

/**
 * ask driver where he is.
 *
 * @param id
 * @param  descriptor of the driver
 * @return If found return Driver instance, else not found exception.
 */
Point TaxiCenter::getDriverLocation(int id) {
    int descriptor =-1;
    // find key by value
    for (auto &i : dataMap) {
        if(id == i.second->driverID){
            descriptor = i.second->driversDescriptors;
            break;
        }
    }
    if (descriptor < 0){
        perror("can't find driver id - in getDriverLocation");
        exit(1);
    }


    socket->sendData(GET_LOCATION,descriptor);
    char buffer[4096];
    size_t bytes = socket->receiveData(buffer,4096,descriptor);
    cout << "received " << descriptor;
    string serial_str(buffer, bytes);
    Point *location;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> location;

    Point dLoc = Point(location->getX(), location->getY());
    cout << "ended " << descriptor;
    // delete location;
    delete(location);
    return dLoc;
}

/**
 * Add a new cab to the station.
 * @param c
 */
void TaxiCenter::addNewCab(Cab *c) {
    cabsList.push_back(c);
}


/**
 * Union of two routes.
 *
 * @param t
 * @param currentLocation
 * @return the union route
 */
queue<Point> TaxiCenter::createDirections (TripInfo t, Point currentLocation) {
    queue<Point> from = calculator.run(*map, t.getStartPoint(), &currentLocation, 1);
    Point start = t.getStartPoint();
    queue<Point> to = calculator.run(*map, t.getEndPoint(), &start, 1);
    Point tamp;

    // We don't want two points that are equal, because the first point in to
    // and the last point in from are the same
    to.pop();
    while (!to.empty()) {
        tamp = to.front();
        from.push(tamp);
        to.pop();
    }

    return from;
}

/**
 * Search for cab by cab id.
 *
 * @param id
 * @return If found return Cab instance, else not found exception.
 */
Cab& TaxiCenter::getCab(int id) {
    for (int i = 0; i < cabsList.size(); i++) {
        if (cabsList[i]->getID() == id) {
            return *cabsList[i];
        }
    }

    // throw exception
    throw std::invalid_argument("Not exist.");
}



/**
 * Set the grid which the taxi center operates on.
 * @param map
 */
void TaxiCenter::setMap(Grid *map) {
    TaxiCenter::map = map;
}

/**
 * Destructor.
 */
TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < cabsList.size(); i++) {
        delete(cabsList[i]);
    }
    for (int i = 0; i< tripsList.size() ; i++) {
        delete (tripsList[i]);
    }
    close();
    //sleep(5);
    delete socket;

}

/**
 * Set the socket for taxi center.
 * @param port
 * @param communicateType

 */
void TaxiCenter::setSocket(int port, char communicateType) {
    if((communicateType=='t')|(communicateType=='T')){
        socket = new Tcp(true,port);
        socket->initialize();

    } else {
            perror("TaxiCenter :: setSocket() :: not imploded op to = " + communicateType);
    }
}


/**
 * Closes the connection.
 * @param  descriptor of the driver
 */
void TaxiCenter::close() {
    for (vector<int>::iterator it = this->driversDescriptors.begin();
                                it != this->driversDescriptors.end(); ++it) {
        socket->sendData(CLOSE, *it);
        //char buffer[100];
        //socket->receiveData(buffer, 100, *it);
        //string config = buffer;
        /*
        if (buffer[0] != CLOSE[0]) {
            perror("connection un-close currently");
        }*/
    }

}

/**
 * Preforms one turn of driving.
 * @param  descriptor of the driver
 */
void TaxiCenter::moveOneStep() {
    // Wait untill all calculations are completed
    for (int i = 0; i < tripsList.size(); i++) {
        // Only wait for threads that didn't finish
        if (!tripsList[i]->getDirections().empty()) {
            pthread_t temp = tripsList[i]->getThread();
            pthread_join(temp, NULL);
        }
    }

    timeCounter++;

    // Create the threads that will run the mission
    for (auto &it : dataMap) {
        DataTypeClass *dt = new DataTypeClass();
        dt->data = it.second;
        dt->socket = socket;
        dt->timeCounter = timeCounter;
        dt->server = this;
        // For purposes of deciding whether to send trip or to send driver order
        dt->trip = NULL;

        Point driverPlace =  dt->data->location;
        for (int j = 0; j < tripsList.size(); j++) {
            TripInfo *tripInfo = tripsList.at(j);
            if(tripInfo->getTime() == timeCounter) {
                if (driverPlace == tripInfo->getStartPoint()) {
                    dt->trip = tripInfo;
                    tripsList.erase(tripsList.begin() + j);
                    // We found the correct trip, stop loop
                    break;
                }
            }
        }

        if (pthread_create(&dt->data->driverThread, NULL, doOneStepThreaded, (void*) dt)) {
            perror("Error");
        }
    }

    // Wait until all threads are finished
    for (auto &it : dataMap) {
        pthread_join(it.second->driverThread, NULL);
    }
}

