#ifndef SERVER_UDP_H
#define SERVER_UDP_H

#include <stdio.h>

#include "../Server.h"
#include "../Exception/Server.h"

class Server_UDP: public Server
{

protected:

public:
    Server_UDP(int);
    bool read();
    bool write(const char *);
};

#endif
