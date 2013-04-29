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

    // 0 our server_in variable
    memset((char *) &server_in, 0, sizeof(server_in));
    
    // Initaize our @mask variable as pselect will jump out on
    // SIGTERM
    sigemptyset (&mask);
    sigaddset (&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, &origmask) < 0)
        throw Exception_Server();
}

/**
 * This function will return our @socket parameter
 *
 * @return int - The @socket protected variable
 */
int Server::getSocketfd()
{
    return socketfd;
}

/**
 * This returns a pointer to the buffer variable
 *
 * @returns char * - The @buffer variable
 */
char * Server::getBuffer()
{
    return buffer;
}

/**
 * This function will set our timeout value
 * Note if it is set to 0, then our select will never return.
 *
 * @param (long)seconds - Number of seconds to timeout
 * @param (long)nanoseconds - Number of nanoseconds to timeout
 */
void Server::setTimeout(long seconds, long nanoseconds)
{
    pselect_timeout.tv_sec = seconds;
    pselect_timeout.tv_nsec = nanoseconds;
}

/**
 * This function will set the @select_read using the @FD_
 * function and the call select, it will also return the value
 * of select
 *
 * @returns int - The value of select
 */
int Server::wait()
{   
    FD_ZERO(&select_read);
    FD_SET(socketfd, &select_read);
    
    return pselect(socketfd+1, &select_read, NULL, NULL, &pselect_timeout, &origmask);
}

/**
 * An empty destructor designed to be virtual
 */
Server::~Server()
{

}
