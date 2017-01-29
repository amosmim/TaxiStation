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
    calculators = new BFSThreadPool(5,  map);
}

/**
 * Receive the order from the client and set the direction.
 *
 * @param t
 */
void TaxiCenter::receiveOrder(TripInfo *t) {

    this->calculators->addTrip(t);
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

    LOG(INFO) << "Add a new driver";

    driverData *dB = new driverData;
    dB->driversDescriptors = descriptor;
    dB->location = Point(0, 0);

    DataTypeClass *dt = new DataTypeClass();
    dt->data = dB;
    dt->cabList = &cabsList;
    dt->socket = socket;

    char buffer[10];
    // receive driver ID
    this->socket->receiveData(buffer, 10, descriptor);
    int driverID = atoi(buffer);


    dB->driverID = driverID;
    dataMap[descriptor] = dB;
    dt->dataMap = &dataMap;
    // Create the driver thread to handle the registration
    pthread_t *driverThread = &(dt->data->driverThread);
    if (pthread_create(driverThread, NULL, addNewDriverThreaded, (void*) dt)) {
        perror("Error");
    }
}

/**
 * In charge of handling the client registration.
 *
 * @param data
 * @return
 */
void *TaxiCenter::addNewDriverThreaded(void *data) {
    DataTypeClass *dt = (DataTypeClass *) data;
    driverData *dB = dt->data;
    Socket *serverSocket = dt->socket;
    std::vector<Cab *> *cabsList = dt->cabList;
    std::map<int, driverData*> *dMap = dt->dataMap;
    pthread_mutex_t lock;


    int driverID = dB->driverID;

    LOG(DEBUG) << "addNewDriverThread started with driver id:" << driverID;


    // send cab serialized
    for (int j = 0; j < cabsList->size(); j++) {
        if (cabsList->at(j)->getID() == driverID) {
            //char buffer2[1000];
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);

            Cab *c = cabsList->at(j);
            oa << c;
            s.flush();
            LOG(DEBUG) << "Cab id:" << c->getID() << " send to driver.";
            serverSocket->sendData(serial_str,dB->driversDescriptors);
            char buffer3[100];
            serverSocket->receiveData(buffer3, 100, dB->driversDescriptors);
            //string config = buffer3;
            if (atoi(buffer3) != cabsList->at(j)->getID()) {
                perror("connection error - addDriver - Cab" + driverID);
            }
            // delete the cab from list
            delete(c);
            pthread_mutex_lock(&lock);
            cabsList->erase(cabsList->begin() + j);
            pthread_mutex_unlock(&lock);

            break;
        }
    }
    pthread_mutex_destroy(&lock);
    delete(dt);
    LOG(DEBUG) << "Thread ended for driver id: " << driverID;
}

/**
 * Assign a single trip to the correct driver. Thread Function.
 * @param data
 * @return
 */
void *TaxiCenter::doOneStepThreaded(void *data) {
    // Assign trip to driver
    DataTypeClass *dB = (DataTypeClass *) data;

    TaxiCenter *taxiCenter = dB->self;

    driverData *driverData = dB->data;
    Socket *serverSocket =  dB->socket;
    int descriptor = dB->data->driversDescriptors;

    LOG(DEBUG) << "doOneStepThread started with client discriptor id:" << descriptor;

    // If there is not current trip to send
    if (dB->trip == NULL) {
        // Send and receive - preform the move one step
        serverSocket->sendData(DRIVE, driverData->driversDescriptors);

        // Double check - if the client received
        char buffer[100];
        serverSocket->receiveData(buffer, 100, driverData->driversDescriptors);

        LOG(DEBUG) << "client discriptor id:" << descriptor << " moved one step";

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

        LOG(DEBUG) << "Sent trip to client discriptor id:" << descriptor;

        char buffer[100];
        serverSocket->receiveData(buffer,100, descriptor);
        if(buffer[0] != GET_TRIPINFO[0]){
            perror("Connection Error - TripInfo send from TaxiCenter");
        }
        // Send serialized tripInfo
        serverSocket->sendData(serial_str,descriptor);

        char buffer2[100];
        serverSocket->receiveData(buffer2,100, descriptor);

        delete(dB->trip);

    }

    driverData->location = taxiCenter->getDriverLocation(driverData->driverID);

    delete((DataTypeClass *)data);
    LOG(DEBUG) << "doOneStepThread ended for client discriptor id:" << descriptor;
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
    for(auto it = dataMap.begin(); it != dataMap.end(); ++it){
        if(id == it->second->driverID){
            //return i.second->location;
            descriptor = it->second->driversDescriptors;
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

    string serial_str(buffer, bytes);
    Point *location;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> location;

    Point dLoc = Point(location->getX(), location->getY());

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
 * Destructor.
 */
TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < cabsList.size(); i++) {
        delete(cabsList[i]);
    }
    for (int i = 0; i< tripsList.size() ; i++) {
        delete (tripsList[i]);
    }

    for(auto it = dataMap.begin(); it != dataMap.end(); ++it){
        delete(it->second);
    }
    this->close();
    delete calculators;
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
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        int descriptor = it->first;
        socket->sendData(CLOSE, descriptor);
        char buffer[100];
        socket->receiveData(buffer, 100, descriptor);
    }


}

/**
 * Preforms one turn of driving.
 * @param  descriptor of the driver
 */
void TaxiCenter::moveOneStep() {
    timeCounter++;
    // Wait until all calculations are completed
    for (int i = 0; i < tripsList.size(); i++) {
        // Only wait for threads that didn't finish
        if (tripsList[i]->getTime() == this->timeCounter)  {
            while(!tripsList[i]->isCalculated()) {
                sleep(1);
            }
        }
    }



    // Create the threads that will run the mission
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        DataTypeClass *dt = new DataTypeClass();
        dt->data = it->second;
        dt->socket = socket;
        dt->timeCounter = timeCounter;
        dt->self = this;
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

        if (pthread_create(&(dt->data->driverThread), NULL, doOneStepThreaded, (void*) dt)) {
            perror("Error");
        }
    }

    // Wait until all threads are finished
    waitForThreads();
}

/**
 * Wait for the threads to finish their work.
 */
void TaxiCenter::waitForThreads() {
    std::map<int, struct driverData*> map = this->dataMap;
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        pthread_join(it->second->driverThread, NULL);
    }
}

/**
 * Get driver location.
 *
 * @param id
 * @param  descriptor of the driver
 * @return If found return Driver instance, else not found exception.
 */
Point TaxiCenter::driverLocation(int id) {
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        if (id == it->second->driverID) {
            return it->second->location;
        }
    }

    perror("wrong driver id");
    return Point(-1,-1);
}
