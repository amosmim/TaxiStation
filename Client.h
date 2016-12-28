//
// Created by amos on 12/28/16.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H


#include "Server.h"

class Client {
private:
    Status getStatusFromChar(char status);
public:
    Client(){}
    int run();
};


#endif //PROJECT_CLIENT_H
