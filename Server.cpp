//
// Created by amos on 12/28/16.
//

#include "Server.h"
int main() {
    // create socket
    /*int mainKey = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    // port 12345
    sin.sin_port = htons(SERVER_PORT);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];

*/

    string input;
    string tamp;
    MainFlowClass mainFlow;
    //mainFlow.setSock(&from);
    int gridX, gridY;

    // Get x and y for grid
    getline(cin, input);

    StringParser sp(input);
    vector<string> parsed = sp.split(' ');

    gridX = atoi(parsed[0].c_str());
    gridY = atoi(parsed[1].c_str());

    // Get obstacles number
    getline(cin, input);

    int obstacles = atoi(input.c_str());
    vector<Point> obstaclesList;
    // Create obstacles list if necessary
    while (obstacles != 0) {
        getline(cin, input);
        sp.setStr(input);
        parsed = sp.split(',');
        int x = atoi(parsed[0].c_str());
        int y = atoi(parsed[1].c_str());
        obstaclesList.push_back(Point(x, y));
        obstacles--;
    }

    mainFlow.setGrid(gridX, gridY, obstaclesList);
    mainFlow.createTaxiStation();
    mainFlow.run();
    return 0;
}



/*ssize_t bytes;
ssize_t sent_bytes;
int driverID;

// all the other input will input there
do {
    cin >> mainKey;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (mainKey == 1) {
        int driversSum = 0;
        cin >> driversSum;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i=0; i < driversSum ; ++i) {
            // communicate with driver - get ID and serialazition
            bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
            if (bytes < 0) {
                perror("error reading from socket");
            }

            driverID = atoi(buffer);
            cout << "Hi! " << driverID << endl;
            //mainFlow.run(mainKey,buffer);
/*
            // send cab details
            tamp = "1,H,R";

            sent_bytes = sendto(sock, tamp.data(), tamp.size(), 0, (struct sockaddr *) &from, sizeof(from));
            if (sent_bytes < 0) {
                perror("error writing to socket");
            }

            // wait for OK
            bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
            if (bytes < 0) {
                perror("error reading from socket");
            }
            if (atoi(buffer) != 1) {
                perror("wrong answer for client! except to 1");
            }

            // send trip details
            tamp = "0,0,0,1,2,4,5";
            //sp.stringToChars(buffer, tamp);
            sent_bytes = sendto(sock, tamp.data(), tamp.size(), 0, (struct sockaddr *) &from, sizeof(from));
            if (sent_bytes < 0) {
                perror("error writing to socket");
            }

            // wait for OK
            bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
            if (bytes < 0) {
                perror("error reading from socket");
            }
            if (atoi(buffer) != 1) {
                perror("wrong answer for client! except to 1");
            }
        }
    } else {
        if (mainKey!=7)
            getline(cin, input);
    }
    //mainFlow.run(mainKey,input);
} while (mainKey != 7);

// program finish massage.
tamp = "-1 ";
sent_bytes = sendto(sock, tamp.data(), tamp.size(), 0, (struct sockaddr *) &from, sizeof(from));
if (sent_bytes < 0) {
    perror("error writing to socket");
}
// wait for OK
bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
if (bytes < 0) {
    perror("error reading from socket");
}
if (atoi(buffer) != -1) {
    perror("wrong answer for client! except to -1");
}


close(sock);*/

