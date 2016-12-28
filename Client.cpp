//
// Created by amos on 12/28/16.
//

#include "Client.h"

int Client::run(){
    const char* ip_address = "127.0.0.1";
    const int port_no = 12345;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);



    string data;
    StringParser sp;

    getline(cin, data);
    sp.setStr(data);
    vector<string> input =  sp.split(',');
    int id = atoi(input[0].c_str());
    int age = atoi(input[1].c_str());
    char status = input[2].at(0);
    int exp = atoi(input[3].c_str());
    int v_id = atoi(input[4].c_str());
    Statistics statistics = Statistics();
    Driver driver = Driver(id,age, getStatusFromChar(status),exp,v_id,&statistics);

    // send ID Number;
    ssize_t sent_bytes = sendto(sock, input[0].data(), input[0].size(), 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
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
    }

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
        }*/
    } while (atoi(buffer) != -1);

    close(sock);
    return 0;

}

Status Client::getStatusFromChar(char status) {

    switch (status) {
        case 'S':
            return Status::SINGLE;

        case 'D':
            return  Status::DIVORCED;

        case 'W':
            return  Status::WIDOWED;

        case 'M':
            return  Status::MARRIED;
        default:
            perror("wrong Status Key! in : " + status );
    }
}