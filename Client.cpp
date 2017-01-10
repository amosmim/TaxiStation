//
// Created by amos on 12/28/16.
//

#include "Client.h"
#include "Commends.h"


int main(int argc,char *argv[]) {
    // default port number
    int port = 46287;
    // get port number from commend line
    if (argc >= 1) {
        port = atoi(argv[1]);
    }

    //Socket *socket = new Udp(false, port);
    Socket *socket = new Tcp(false, port);
    socket->initialize();
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
    socket->sendData(input[0].c_str()); // send driver id
   /* char buffer[10];
    socket->receiveData(buffer, 10);
    int idOK = atoi(buffer);
    if (idOK != id) {
        perror("connection error - client 1");
    }*/
    // get cab serialization
    char buffer1[4096];
    size_t bytes = socket->receiveData(buffer1, 4096);

    string serial_str(buffer1, bytes);

    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    Cab *myCab;
    ia >> myCab;

    // attach cab to driver
    driver.setCab(myCab);
    //cout << "my cab Id is: " << myCab->getID() << " " << myCab->canMove() << endl;
    std::string bufferCab = std::to_string(myCab->getID());
    socket->sendData(bufferCab);
    bool running = true;
    // get tripinfo serialization
    do{
        char buffer2[4096];

        bytes = socket->receiveData(buffer2, 4096);
        string commend_str(buffer2, bytes);
        //char commend = buffer2[0];

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
            socket->sendData(serial_str3);
            delete(sP); // no need for this pointer
        } else {
            if(buffer2[0] == GET_TRIPINFO[0]){
                // get tripInfo
                socket->sendData(buffer2);
                char Tripbuffer[4096];
                // get tripinfo from server
                bytes = socket->receiveData(Tripbuffer, 4096);
                string trip_serial_str(Tripbuffer, bytes);
                boost::iostreams::basic_array_source<char> tripsource(trip_serial_str.c_str(), bytes);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(tripsource);
                boost::archive::binary_iarchive tia(s3);
                TripInfo *tripInfo;
                tia >> tripInfo;
                driver.setTripInfo(tripInfo);
            } else {
                if (buffer2[0] == DRIVE[0]) {
                    socket->sendData(buffer2);
                    driver.driveTo();
                } else {
                    if (buffer2[0] == CLOSE[0]) {
                        int work;
                        do {
                            work = socket->sendData(buffer2);
                        } while (work == -1);

                        running = false;

                    }
                }
            }

        }
    } while (running);

    delete (socket);
    return 0;
}
