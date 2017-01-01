
##########################
# 301236287   302933833  #
# maimona5    ziporio    #
##########################
a.out: main.o StringParser.o BFS.o grid.o point.o Node.o Key.o Graph.o Driver.o Cab.o StandardCab.o LuxuryCab.o TaxiCenter.o TripInfo.o MainFlowClass.o Passenger.o Statistics.o Udp.o Socket.o
	g++ -std=c++0x main.o StringParser.o BFS.o grid.o point.o Node.o Key.o Graph.o Driver.o Cab.o StandardCab.o LuxuryCab.o TaxiCenter.o TripInfo.o MainFlowClass.o Passenger.o Statistics.o Udp.o Socket.o -lboost_serialization

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++0x StringParser.cpp

Key.o: Key.cpp Key.h
	g++ -c -std=c++0x Key.cpp

Graph.o: Graph.cpp Graph.h Key.h
	g++ -c -std=c++0x Graph.cpp

BFS.o: BFS.cpp BFS.h point.h grid.h Node.h Key.h Graph.h
	g++ -c -std=c++0x BFS.cpp

grid.o: grid.cpp grid.h point.h Node.h Graph.h
	g++ -c -std=c++0x grid.cpp

point.o: point.cpp point.h Key.h
	g++ -c -std=c++0x point.cpp -lboost_serialization

Node.o: Node.cpp Node.h point.h
	g++ -c -std=c++0x Node.cpp -lboost_serialization

Statistics.o: Statistics.cpp Statistics.h
	g++ -c -std=c++0x Statistics.cpp

Cab.o: Cab.cpp Cab.h
	g++ -c -std=c++0x Cab.cpp -lboost_serialization

Driver.o: Driver.cpp Driver.h Statistics.h
	g++ -c -std=c++0x Driver.cpp -lboost_serialization

StandardCab.o: StandardCab.cpp StandardCab.h Cab.h CarType.h CarColor.h CabType.h Status.h
	g++ -c -std=c++0x StandardCab.cpp -lboost_serialization

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h Cab.h CarType.h CarColor.h CabType.h Status.h
	g++ -c -std=c++0x LuxuryCab.cpp -lboost_serialization

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h
	g++ -c -std=c++0x TaxiCenter.cpp

TripInfo.o: TripInfo.cpp TripInfo.h
	g++ -c -std=c++0x TripInfo.cpp -lboost_serialization

Passenger.o: Passenger.cpp Passenger.h
	g++ -c -std=c++0x Passenger.cpp -lboost_serialization

MainFlowClass.o: MainFlowClass.cpp MainFlowClass.h
	g++ -c -std=c++0x MainFlowClass.cpp

#Client.o: Client.cpp Client.h
#	g++ -c -std=c++0x Client.cpp

#Server.o: Server.cpp Server.h
#	g++ -c -std=c++0x Server.cpp

Socket.o: Socket.cpp Socket.h
	g++ -c -std=c++0x Socket.cpp

Udp.o: Udp.cpp Udp.h
	g++ -c -std=c++0x Udp.cpp


main.o: main.cpp point.h grid.h BFS.h StringParser.h MainFlowClass.h TripInfo.h Statistics.h
	g++ -c -std=c++0x main.cpp -lboost_serialization





