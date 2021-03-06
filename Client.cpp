/**
 * Amos Maimon And Or Zipori.
 *
 */

#include "Client.h"
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc,char *argv[]) {
    // default port number
    int port = 46287;
    // get port number from commend line
    if (argc > 2) {
        port = atoi(argv[2]);
    }

    LOG(INFO) << "Client started";

    Socket *socket = new Tcp(false, port);
    int success = socket->initialize();
    if (success <= 0) {
        perror("ERROR in Client - from initialize");
        return 1;
    }
    string data;
    StringParser sp;

    // get driver info from user
    getline(cin, data);
    sp.setStr(data);
    vector<string> input = sp.split(',');
    int id = atoi(input[0].c_str());
    int age = atoi(input[1].c_str());
    Status stat = sp.getStatusFromChar(input[2].at(0));
    int exp = atoi(input[3].c_str());
    int v_id = atoi(input[4].c_str());

    // create driver object with input
    Driver driver = Driver(id, age, stat, exp, v_id);
    string tamp = data;
    // send ID Number;
    socket->sendData(input[0].c_str(),1); // send driver id

    // get cab serialization
    char buffer1[4096];
    int bytes = socket->receiveData(buffer1, 4096,1);

    string serial_str(buffer1, bytes);

    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    Cab *myCab;
    ia >> myCab;


    // attach cab to driver
    driver.setCab(myCab);

    LOG(DEBUG) << "Driver " << id << " received a cab";
    std::string bufferCab = std::to_string((long long int)myCab->getID());
    socket->sendData(bufferCab,1);
    bool running = true;
    // get mission
    do{
        char buffer2[4096];
        // get order type
        bytes = socket->receiveData(buffer2, 4096,1);
        string commend_str(buffer2, bytes);

        if (buffer2[0] == GET_LOCATION[0]) {
            // send location point to server
            Point location = driver.getCurrentLocation();
            // We serialize object on the heap inorder to deserialize it properly
            Point *sP = new Point(location.getX(), location.getY());
            std::string serial_str3;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str3);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);

            oa << sP;
            s.flush();
            // send location
            socket->sendData(serial_str3,1);
            delete(sP); // no need for this pointer
            LOG(DEBUG) << "Location send";
        } else {
            if(buffer2[0] == GET_TRIPINFO[0]){
                // get tripInfo
                socket->sendData(buffer2,1);
                char Tripbuffer[130000];
                // get tripinfo from server
                bytes = socket->receiveData(Tripbuffer, 130000,1);
                string trip_serial_str(Tripbuffer, bytes);
                boost::iostreams::basic_array_source<char> tripsource(trip_serial_str.c_str(), bytes);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(tripsource);
                boost::archive::binary_iarchive tia(s3);
                TripInfo *tripInfo;
                tia >> tripInfo;
                driver.setTripInfo(tripInfo);
                socket->sendData(Tripbuffer,1);
                LOG(DEBUG) << "Trip received";
            } else {
                if (buffer2[0] == DRIVE[0]) {
                    socket->sendData(buffer2,1);
                    driver.driveTo();
                    LOG(DEBUG) << "Moving";
                } else {
                    if (buffer2[0] == CLOSE[0]) {
                        socket->sendData(buffer2,1);
                        delete (socket);

                        running = false;
                        LOG(INFO) << "Client ended.";

                    }
                }
            }

        }
    } while (running);


    return 0;
}
