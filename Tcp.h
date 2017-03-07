/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef TCP_H_
#define TCP_H_

#include "Socket.h"

class Tcp: public Socket {
private:
	//int descriptorCommunicateClient;
public:
	/***********************************************************************
	* function name: Tcp												   *
	* The Input: Boolean, true - if server, false if client and port number*
	* The output: none										               *
	* The Function operation: creating new Tcp						       *
	***********************************************************************/
	Tcp(bool isServers, int port_num);
	/***********************************************************************
	* function name: ~Tcp												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: default destructor					       *
	***********************************************************************/
	virtual ~Tcp();
	int initialize(string ip);
	int initialize();
	/***********************************************************************
	* function name: sendData											   *
	* The Input: string data to send and descriptor Communicate of Client  *
	*     in server case or any number in Client case.                     *
	* The output: number of bytes that gets                 	           *
	* The Function operation: sending the required data, using his length  *
	* and the socket descriptor or client descriptor.					   *
	***********************************************************************/
	int sendData(string data, int descriptorCommunicateClient);
	/***********************************************************************
	* function name: receiveData										   *
	* The Input: buffer to send and is size, and also - descriptor         *
	*   Communicate Client in server case or any number in client case     *
	* The output: int number representing the return status	               *
	* The Function operation: getting data from the other socket to,	   *
	* enter it to the buffer and print the data							   *
	***********************************************************************/
	int receiveData(char *buffer, int size, int descriptorCommunicateClient);

	/***********************************************************************
	* function name: acceptOneClient									   *
	* The Input: None                                                      *
	* The output: int number representing the descriptorCommunicateClient  *
	*    if it server or no-negative integer in client case                *
    *    or -1 when failed.                                                *
	* The Function operation: getting data from the other socket to,	   *
	* enter it to the buffer and print the data							   *
	***********************************************************************/
	int acceptOneClient();
};

#endif /* TCP_H_ */
