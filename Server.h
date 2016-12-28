//
// Created by amos on 12/28/16.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H


#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <queue>
#include "point.h"
#include "StringParser.h"
#include "MainFlowClass.h"
#include <sys/socket.h>
#include <netinet/in.h>



class Server {
#define SERVER_PORT 12345
public:
    Server(){};
    int run();
};


#endif //PROJECT_SERVER_H
