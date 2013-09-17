#include "Server.h"

/**
 * Constructor.
 *
 * This function will initialize the @p port value which is passed as a parameter
 * it will also set the Server::client_in_length value to be the sizeof Server::client_in 
 * and set the server_in to have all 0's as its value.
 *
 * @param port The value of the port
 */
Server::Server(unsigned int port)
{
    this->port = port;
    
    client_in_length = sizeof(client_in);

    // 0 our server_in variable
    memset((char *) &server_in, 0, sizeof(server_in));
    
    // Initaize our mask variable as pselect will jump out on
    // SIGTERM
    memset((sigset_t *)&mask, 0, sizeof(mask));
    sigemptyset (&mask);
    sigaddset (&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, &origmask) < 0)
        throw Exception_Server();
}

/**
 * This function will return our @a socket parameter.
 *
 * @returns The Server::socketfd protected variable
 */
int Server::getSocketfd()
{
    return socketfd;
}

/**
 * This returns a pointer to the buffer variable.
 *
 * @returns The Server::buffer variable
 */
unsigned char * Server::getBuffer()
{
    return buffer;
}

/**
 * Set timeout values.
 *
 * This function will set our timeout value
 * Note if it is set to 0, then our select will never return.
 *
 * @param seconds Number of seconds to timeout
 * @param miliseconds Number of nanoseconds to timeout
 */
void Server::setTimeout(const unsigned int seconds, const unsigned int miliseconds)
{
    if (miliseconds > 999)
        throw Exception_Server("SetTimeout set to value that is not between 0-999");
        
    pselect_timeout.tv_sec = seconds;
    pselect_timeout.tv_nsec = miliseconds * 1000000l;
}

/**
 * Wait using pselect or timeout.
 *
 * This function will set the @a select_read using the @a FD_
 * function and the call select, it will also return the value
 * of select
 *
 * @returns The value returned by @p pselect
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
