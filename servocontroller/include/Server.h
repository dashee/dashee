/**
 * This is a class designed to be overwritten, 
 * It sets the basics required for a server to be initiated however,
 * it does not implement the major functionality
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

#include "Exception/Server.h"

#ifndef SERVER_H_
#define SERVER_H_

#define SERVER_BUFFER_SIZE 32

class Server
{

protected:

    /** 
     * This is our filedescriptor for our socket
     */
    int socketfd;

    /**
     * set by our constructor this is the port
     * the server will listen on
     */ 
    int port;
    
    /** 
     * This holds the information required
     * to start our server.
     */
    struct sockaddr_in server_in;
    
    /**
     * Initialize our client socket settings
     * this is used to communicate back to the client
     * and set by our @read() function
     */
    struct sockaddr_in client_in;

    /** 
     * recvfrom takes an int * for the length.
     * so we initialize the client lenght into a variable
     */
    int client_in_length;
    
    /** 
     * This is the buffer size used for our project
     * it usually should be set to 2 bytes, and longer
     * commands should just reread the buffer till its empty
     */ 
    unsigned char buffer[SERVER_BUFFER_SIZE];

    /** 
     * Set our select timeout
     */
    struct timespec pselect_timeout;

    /**
     * Our read select fd
     */
    fd_set select_read;
    
    /** 
     * This is our mask set in the constructor which is 
     * required by pselect
     */
    sigset_t mask;
    sigset_t origmask;

    // Set the port and initialize our server and client variables
    Server(int port);
    
    //Creates a read select
    int wait();

public:
    
    // Get the @socketfd
    int getSocketfd();

    // Get the @buffer
    unsigned char * getBuffer();
    
    // Set our timeout value
    void setTimeout(long, long = 0);
    
    // Read from the client
    virtual bool read() = 0;

    // Write back to our client
    virtual bool write(const char *) = 0;
    
    // An empty virtual desructor
    virtual ~Server();
};

#endif
