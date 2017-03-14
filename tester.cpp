//
// Created by amos on 1/30/17.
//

#include "tester.h"
#include "Socket.h"
#include "Tcp.h"


using namespace std;

int main() {

    Tcp socket = Tcp(true, 45454);
    socket.initialize("172.0.0.1");
    int dis  = socket.acceptOneClient();
    socket.sendData("Hello\n", dis);
    char buff[1000];

    int rec = socket.receiveData(buff, 1000,dis);
    string serial_str(buff, rec);
    cout << rec << endl <<buff ;
    socket.sendData("Bye!!!\n", dis);


        return 0;
}
