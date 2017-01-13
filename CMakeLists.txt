cmake_minimum_required(VERSION 3.6)

project(TaxiStation)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
#set(BOOST_ROOT CACHE PATH "/Users/guest/Desktop/ex2-3/TaxiStation/boost")

find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(core_SRCS point.cpp DataTypeClass.cpp DataTypeClass.h point.h BFS.cpp BFS.h Node.cpp Node.h grid.cpp grid.h StringParser.cpp StringParser.h Graph.cpp Graph.h Key.cpp Key.h Passenger.cpp Passenger.h TripInfo.cpp TripInfo.h Statistics.cpp Statistics.h CarColor.h CarType.h Driver.cpp Driver.h LuxuryCab.cpp LuxuryCab.h StandardCab.cpp  Status.h TaxiCenter.cpp TaxiCenter.h StandardCab.h Cab.cpp MainFlowClass.cpp MainFlowClass.h CabType.h Server.cpp Server.h Client.cpp Client.h Socket.cpp Socket.h Commends.h Tcp.cpp Tcp.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_library(core ${core_SRCS})

add_executable(server Server.cpp )
add_executable(client Client.cpp )
target_link_libraries(core ${Boost_LIBRARIES})
target_link_libraries(server core ${Boost_LIBRARIES})
target_link_libraries(client core ${Boost_LIBRARIES})
