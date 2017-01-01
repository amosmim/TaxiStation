/**
 * Amos Maimon And Or Zipori.
 *
 * TaxiCenter Implementation.
 */

#include <sys/socket.h>
#include "TaxiCenter.h"
#include "Udp.h"

/**
 * Constructor.
 * @param grid
 * @return
 */
TaxiCenter::TaxiCenter(Grid* grid) {
    map = grid;
}

/**
 * Receive the order from the client and set the direction.
 *
 * @param t
 */
void TaxiCenter::receiveOrder(TripInfo *t) {
    Point start = t->getStartPoint();
    t->setDirections(calculator.run(*map, t->getEndPoint(), &start, 1));
    tripsList.push(t);
}

/**
 * Set the statistics instance for the current run.
 * @param s
 *//*
void TaxiCenter::setStatistics(Statistics *s) {
    stats = s;
}
*/
/**
 * Get the statistics instance.
 * @return Statistics
 *//*
Statistics* TaxiCenter::getStatistics() {
    return stats;
}*/

/**
 * Add a new driver to the station.
 * @param d
 */
void TaxiCenter::addNewDriver() {
    /*for (int j = 0; j < cabsList.size(); j++) {
        if (cabsList[j]->getID() == d->getVehicleID()) {
            d->setCab(cabsList[(size_t) j]); //get cab id inside driver
        }
    }
    driversInfo.push_back(d);*/
    char buffer[10];
    // receive driver ID
    int work = socket->receiveData(buffer, 10);
    int driverID = atoi(buffer);
    socket->sendData("ID-OK");
    driversID.push_back(driverID);
    //cout << driverID;
    // send cab serialized
    for (int j = 0; j < cabsList.size(); j++) {
        if (cabsList[j]->getID() == driverID) {
            char buffer2[1000];
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);

            Cab *c = cabsList[j];
            oa << c;
            s.flush();

            //cout << "Before :" << serial_str.size() << endl;
            //Cab *d2;
            //boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
            //boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            //boost::archive::binary_iarchive ia(s2);
            //ia >> d2;

            //cout << d2->getID()<<endl;
            //cout << d2->canMove()<<endl;

            socket->sendData(serial_str);
            char buffer3[100];
            socket->receiveData(buffer3, 100);
            string config = buffer3;
            if (config != "CAB-OK") {
                perror("connection error - addDriver - Cab" + driverID);
            }
            // delete the cab from list
            cabsList.erase(cabsList.begin() + j);
            break;
        }
    }
}

void TaxiCenter::assignTrips() {
    Point driverPlace;
    // Assign trip to driver
    while(!tripsList.empty()){
        if (driversID.size() < tripsList.size()) {
            throw std::invalid_argument("To Much Trips");
        }
        for (int i = 0; i < driversID.size(); i++) {
            TripInfo *tripInfo = tripsList.front();
            // driverPlace = stats->getLocationByID(driversInfo[i]->getID());

            driverPlace = getDriverLocation(i);
            //if ((driverPlace == tripInfo->getStartPoint())&&(driversInfo[i]->isAvailable())) {
            if (driverPlace == tripInfo->getStartPoint()) {
                tripInfo->setDirections(createDirections(*tripInfo, driverPlace));
                //driversInfo[i]->setTripInfo(tripInfo);

                // serialized tripInfo
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                //TripInfo tripInfo1= *tripInfo;
                oa << tripInfo;
                s.flush();
                // send tripinfo
                socket->sendData(GET_TRIPINFO);
                socket->sendData(serial_str);
                tripsList.pop();
            }
        }
    }


}




/**
 * ask driver where he is.
 *
 * @param id
 * @return If found return Driver instance, else not found exception.
 */

Point TaxiCenter::getDriverLocation(int id) {
    socket->sendData(GET_LOCATION);
    char buffer[1000];
    socket->receiveData(buffer,1000);
    string serial_str;
    Point *location;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> location;
    //Point loc = *location;
   // delete location;
    return *location;
}

/**
 * Add a new cab to the station.
 * @param c
 */
void TaxiCenter::addNewCab(Cab *c) {
    cabsList.push_back(c);
}

/**
 * Get the queue of the trips.
 * @return queue
 */
queue<TripInfo *> TaxiCenter::getTripList() {
    return tripsList;
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
    //Cab* cab = new LuxuryCab(1,CarType::FIAT, CarColor::RED, 100);
    //return *cab;
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
    // close connections with drivers.
    close();
    /*
    for (int i = 0; i < driversInfo.size(); i++) {
        delete(driversInfo[i]);
    }*/
}

void TaxiCenter::setSocket(int port, char communicateType) {
    if ((communicateType=='u')|(communicateType=='U')) {
        socket = new Udp(true,port);
        socket->initialize();
    } else {
        perror("TaxiCenter :: setSocket() :: not imploded op to = " + communicateType);
    }
}

void TaxiCenter::close() {
    socket->sendData(CLOSE);
    char buffer[100];
    socket->receiveData(buffer, 100);
    string config = buffer;
    if (config != "CLOSE-OK") {
        perror("connection un-close currently");
    }
    delete socket;
}

void TaxiCenter::moveOneStep() {
    assignTrips();
    // tell driver to move on step
    socket->sendData(DRIVE);

}






/**
 * Add a new driver to the station. - network version
 * @param d
 * @param from socket
 *//*
void TaxiCenter::addNewDriver(Driver *d) {

    for (int j = 0; j < cabsList.size(); j++) {
        if (cabsList[j]->getID() == d->getVehicleID()) {
            d->setCab(cabsList[(size_t) j]); //get cab id inside driver
            int sock = 3;
            char buffer[200];
            string tamp = "Cab's serialization here!!!";
            unsigned int from_len = sizeof(struct sockaddr);
            ssize_t sent_bytes = sendto(sock, tamp.data(), tamp.size(), 0, (struct sockaddr *) from, sizeof(from));
            if (sent_bytes < 0) {
                perror("error writing to socket");
            }

            // wait for OK
            ssize_t bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) from, &from_len);
            if (bytes < 0) {
                perror("error reading from socket");
            }
            if (atoi(buffer) != 1) {
                perror("wrong answer for client! except to 1");
            }
            break;
        }
    }
    driversInfo.push_back(d);



}
*/

/*
Driver TaxiCenter::getDriver(int id) {
    for (int i = 0; i < driversInfo.size(); i++) {
        if (driversInfo[i]->getID() == id) {
            return *driversInfo[i];
        }
    }

    // throw exception
    throw std::invalid_argument("Not exist.");
}*/


/**
 * Move the taxi drivers around for their objectives.
 *
 * @return true if all drivers finnised.
 */
/*bool TaxiCenter::start() {
    int driversCount;
    freeDrivers = 0;
    for (int j = 0; j < driversInfo.size(); j++) {
        if (driversInfo[j]->isAvailable()) {
            freeDrivers++;
        }
    }
    /*
    vector<Driver *> tamp;
    Point driverPlace;
    // Assign trip to driver

    while(!tripsList.empty()){
        if (driversInfo.size() < tripsList.size()) {
            throw std::invalid_argument("To Much Trips");
        }
        for (int i = 0; i < driversInfo.size(); i++) {
            TripInfo *t = tripsList.front();
           // driverPlace = stats->getLocationByID(driversInfo[i]->getID());

            driverPlace = getDriver(i).getCurrentLocation();
            if ((driverPlace == t->getStartPoint())&&(driversInfo[i]->isAvailable())) {
                t->setDirections(createDirections(*t, driverPlace));
                driversInfo[i]->setTripInfo(t);
                tripsList.pop();
                tamp.push_back(driversInfo[i]);

            }
        }
    }*/

// Make the drivers start driving
/*int i = 0;
while(!tamp.empty()) {
    if(tamp[i]->driveTo()) {
        tamp.erase(tamp.begin() + i);
    }
    i++;
    if (i >= tamp.size()) {
        i = 0;
    }
}

// Finished
return true;
}*/
