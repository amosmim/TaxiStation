//
// Created by amos on 12/28/16.
//

#include "Client.h"
#include "Commends.h"

int main() {
    const char *ip_address = "127.0.0.1";
    const int port = 12345;
    /*int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);*/


    Socket *socket = new Udp(false, port);
    socket->initialize();
    string data;
    StringParser sp;

    //std::string str ("Test \0string");
    //cout << str.size();

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
    char buffer[4096];
    socket->receiveData(buffer, 4096);
    string config = buffer;
    if (config != "ID-OK") {
        perror("connection error - client 1");
    }
    // get cab serialization
    char buffer1[4096];
    size_t bytes = socket->receiveData(buffer1, 4096);

    string serial_str(buffer1, bytes);
    //char *end = buffer+4095;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    Cab *myCab;
    ia >> myCab;


    cout << "my cab Id is: " << myCab->getID() << endl;
    socket->sendData("CAB-OK");
    bool running = true;
    // get tripinfo serialization
    do{
        char buffer2[4096];

        bytes = socket->receiveData(buffer2, 4096);
        string commend_str(buffer2, bytes);
        char commend = buffer2[0];
        cout << "get from server: " << commend_str<<endl;
        if (buffer2[0] == GET_LOCATION[0]) {
            // send location point to server
            Point location = driver.getCurrentLocation();
            std::string serial_str3;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str3);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);

            oa << location;
            s.flush();
            // send location
            socket->sendData(serial_str3);
        } else {
            if(buffer2[0] == GET_TRIPINFO[0]){
                // get tripInfo

                char Tripbuffer[4096];
                bytes = socket->receiveData(Tripbuffer, 4096);

                string trip_serial_str(Tripbuffer, bytes);
                //char *end = buffer+4095;
                boost::iostreams::basic_array_source<char> tripsource(trip_serial_str.c_str(), bytes);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(tripsource);
                boost::archive::binary_iarchive tia(s3);

                TripInfo *tripInfo;

                tia >> tripInfo;
                driver.setTripInfo(tripInfo);
            } else {
                if (buffer2[0] == DRIVE[0]) {
                    driver.driveTo();
                } else {
                    if (buffer2[0] == CLOSE[0]) {
                        socket->sendData("CLOSE-OK");
                        running = false;

                    }
                }
            }

        }
    } while (running);


    delete socket;
    return 0;
}





/*
    string serial_str1(buffer2, bytes);
    //char *end = buffer+4095;
    boost::iostreams::basic_array_source<char> tripser(serial_str1.c_str(),  bytes);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(tripser);
    boost::archive::binary_iarchive iat(s3);

    TripInfo *myWaze;
    iat >> myWaze;


    cout <<"I will go to: " << myWaze->getEndPoint() << endl;




   // ssize_t sent_bytes = sendto(sock, input[0].data(), input[0].size(), 0, (struct sockaddr *) &sin, sizeof(sin));
   /* ssize_t sent_bytes = sendto(sock, data.data(), data.size(), 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);

    ssize_t bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    cout << "The server sent: " << buffer << endl;

    // send ok
    data = "1 ";
    //data[0] = '1';
    //data[1] = '\0';
    sendto(sock, data.data(), data.size(), 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }*/

/*
    // get cab
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The server sent: " << buffer << endl;

    // send ok
    data = "1 ";
    //data[0] = '1';
    //data[1] = '\0';
    sendto(sock, data.data(), data.size(), 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // get trip
    do {
        recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
        if (bytes < 0) {
            perror("error reading from socket");
        }

        cout << "The server sent: " << buffer << endl;

        // send ok
        if (atoi(buffer) == -1) {
            // exit ok
            data = "-1 ";
        } else {
            // new trip ok
            data = "1 ";
        }
        //data[0] = '1';
       // data[1] = '\0';
        sendto(sock, data.data(), data.size(), 0, (struct sockaddr *) &sin, sizeof(sin));
        if (sent_bytes < 0) {
            perror("error writing to socket");
        }
        /*
        if (atoi(buffer) == -1) {
            return 0;
        }
    } while (atoi(buffer) != -1);

    close(sock);*/



