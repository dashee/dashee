/**
 * @file src/Server/UDP.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef SERVER_UDP_H_
#define SERVER_UDP_H_

#include <stdio.h>

#include "../Server.h"
#include "../Exception/Server/Signal.h"

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
