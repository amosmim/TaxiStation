//
// Created by amos on 12/28/16.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H


#include "Server.h"
#include "Driver.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/deque.hpp>
#include <sstream>
#include <iostream>
#include <queue>
#include "Commends.h"
#include "Cab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"

class Client {
private:

public:
    Client(){}

};


#endif //PROJECT_CLIENT_H
