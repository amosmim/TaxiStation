#include <iostream>
#include <queue>
#include "point.h"
#include "StringParser.h"
#include "MainFlowClass.h"
#include "Client.h"
#include "Server.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/deque.hpp>
#include <sstream>

#include "Socket.h"
#include "Udp.h"
#include "Driver.h"

using namespace std;
using namespace boost::archive;
void save()
{
    Passenger p = Passenger(Point(1,0), Point(2,0));
    vector<Passenger> a;
    a.push_back(p);
    TripInfo *n = new TripInfo(1, Point(1,0), Point(2,0), a,2);

    Driver *d = new Driver(1,2,Status::MARRIED,2,0);

    Cab *c = new LuxuryCab(11, CarType::TESLA, CarColor::BLUE, 22);

    d->setCab(c);

    deque<Point> koko;
    koko.push_front(Point(1,1));
    d->setTripInfo(n);

    // How to use the serialize function
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << d;
    s.flush();

    cout << serial_str << endl;

    Driver *d2;
    deque<Point> k;

    // How to deserialize
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d2;

    cout << d2->getID()<<endl;
    std::cout << static_cast<std::underlying_type<Status>::type>(d2->getStatus()) << std::endl;
    cout << d2->getCab()->getID();


    delete(c);
    delete(n);
    delete(d2);
    delete(d);
}


/**
 * Main  of the program.
 *
 * @return 0
 */
int main(int argc,char *argv[]) {
    // main driver statistics taxicenter trip
/*
    MainFlowClass mainFlow;
    int gridX, gridY;
    string input;
    // Get x and y for grid
    getline(cin, input);

    StringParser sp(input);
    vector<string> parsed = sp.split(' ');

    gridX = atoi(parsed[0].c_str());
    gridY = atoi(parsed[1].c_str());

    // Get obstcales number
    getline(cin, input);

    int obstcales = atoi(input.c_str());
    vector<Point> obstaclesList;
    // Create obstacles list if necessary
    while (obstcales != 0) {
        getline(cin, input);
        sp.setStr(input);
        parsed = sp.split(',');
        int x = atoi(parsed[0].c_str());
        int y = atoi(parsed[1].c_str());
        obstaclesList.push_back(Point(x, y));
        obstcales--;
    }

    mainFlow.setGrid(gridX, gridY, obstaclesList);
    mainFlow.createTaxiStation();
    // all the other input will input there
    mainFlow.run();
*/
/*
    if (atoi(argv[1]) == 1) {
        Client client = Client();
        return client.run();
    } else if (atoi(argv[1]) == 2) {
        Server server = Server();
        return server.run();
    } else {
        cout << "no args input ..." << endl;
    }


*/
    Socket *socket1;

    if (atoi(argv[1]) == 1) {
        // client
        socket1 = new Udp(false, 12345);
        socket1->initialize();
        socket1->sendData("Hello! from client 1");
        char buffer[1000];
        socket1->receiveData(buffer,1000);
        cout << buffer << endl;
    } else if (atoi(argv[1]) == 2) {
        // server
        socket1 = new Udp(true, 12345);
        socket1->initialize();
        char buffer[1000];
        socket1->receiveData(buffer,1000);
        cout << buffer << endl;
        socket1->sendData("hello! from server!");
    } else {
        cout << "no args input ..." << endl;
    }
    delete socket1;
     //  save();




    return 0;
}
