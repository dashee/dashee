/**
 * This is our UDP server class, it does read and write, and sets the port
 * Our variables are set in the base class Server
 *
 * @author Shahmir Javaid
 */

#include <stdio.h>

#include "../Server.h"
#include "../Exception/Server/Signal.h"

#ifndef SERVER_UDP_H_
#define SERVER_UDP_H_

class Server_UDP: public Server
{

protected:

public:
    //call socket given a port
    Server_UDP(int);

    //Read bytes
    bool read();
    
    //Read bytes, given a timeout
    bool read(long, long = 0);

    //Write bytes from the reciever
    bool write(const char *);
};

#endif
