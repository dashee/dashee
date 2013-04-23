#include "Server.h"

Server::Server(int port)
{
    this->port = port;

    client_in_length = sizeof(client_in);
    memset((char *) &server_in, 0, sizeof(server_in));
}

