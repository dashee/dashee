/**
 * This is our UDP server class.
 *
 * It does read and write, and sets the port. 
 * Our variables are set in the base class Server.
 *
 * We can also set timeouts, which will allow the read to timeout so the user can
 * perform other cleanup tasks, by default you can set the timeout by using the base
 * class Server::setTimeout, or pass it directly through read.
 *
 * Note write should only work if and only if a read has returned.
 *
 * @author Shahmir Javaid
 */

#ifndef SERVER_UDP_H_
#define SERVER_UDP_H_

#include <stdio.h>

#include "../Server.h"
#include "../Exception/Server/Signal.h"

class ServerUDP: public Server
{

protected:

public:
    //call socket given a port
    ServerUDP(unsigned int);

    //Read bytes
    bool read();
    
    //Read bytes, given a timeout
    bool read(const unsigned int, const unsigned int = 0);

    //Write bytes from the reciever
    bool write(const char *);
};

#endif
