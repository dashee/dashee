#include "Server.h"

/**
 * This function will initialize the @port value which is passed as a parameter
 * it will also set the @client_in_length value to be the sizeof @client_in 
 * and set the server_in to have all 0's as its value.
 *
 * @param (int)port - The value of the port
 */
Server::Server(int port)
{
    this->port = port;

    client_in_length = sizeof(client_in);
    memset((char *) &server_in, 0, sizeof(server_in));
}

