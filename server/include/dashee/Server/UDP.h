/**
 * @file include/dashee/Server/UDP.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVER_UDP_H_
#define DASHEE_SERVER_UDP_H_

#include <stdio.h>

#include <dashee/Server.h>

namespace dashee
{
    class ServerUDP;
}

/**
 * UDP server class.
 *
 * It does read and write, and sets the port. 
 * Our variables are set in the base class Server.
 *
 * We can also set timeouts, which will allow the read to timeout so the user can
 * perform other cleanup tasks, by default you can set the timeout by using the base
 * class Server::setTimeout, or pass it directly through read.
 *
 * Note write should only work if and only if a read has returned.
 */
class dashee::ServerUDP: public dashee::Server
{

protected:

public:
    //call socket given a port
    ServerUDP(unsigned int port);

    //Read bytes
    void process();
    
    //Read bytes, given a timeout
    bool read();

    //Write bytes from the reciever
    bool write(const char * string);
};

#endif
