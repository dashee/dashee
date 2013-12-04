/**
 * @file include/dashee/Server.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVER_H_
#define DASHEE_SERVER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <queue>

#include <dashee/Log.h>
#include <dashee/Exception/Server.h>
#include <dashee/Exception/OutOfBounds.h>

namespace dashee
{
    class Server;
}

/**
 * Maximum size of the buffer.
 */ 
#define SERVER_BUFFER_SIZE 32

/**
 * An abstract Server class.
 *
 * This is a class designed to be overwritten, It sets the basics 
 * required functionality for a server to be initiated. Future classes
 * such as UDP or TCP can overwrite this
 */
class dashee::Server
{

protected:

    /** 
     * Socket handler.
     *
     * This is our filedescriptor for our socket
     */
    int socketfd;

    /**
     * Port number.
     *
     * set by our constructor this is the port
     * the server will listen on
     */ 
    unsigned int port;
    
    /** 
     * Socket address for the server.
     *
     * This holds the information required
     * to start our server.
     */
    struct sockaddr_in server_in;
    
    /**
     * Socket addresss for the client.
     *
     * Initialize our client socket settings
     * this is used to communicate back to the client
     * and set by our @a read() function
     */
    struct sockaddr_in client_in;

    /** 
     * Socket client address length.
     *
     * recvfrom takes an int * for the length.
     * so we initialize the client lenght into a variable
     */
    int client_in_length;
    
    /** 
     * The maximum size of the read/write buffer.
     *
     * This is the buffer size used for our project
     * it usually should be set to 2 bytes, and longer
     * commands should just reread the buffer till its empty
     */ 
    unsigned char buffer[SERVER_BUFFER_SIZE];

    /**
     * The number of bytes read from a packet into the buffer.
     *
     * This value is set by read() function, by default
     * this will return 0;
     */
    size_t numberOfBytesInBuffer;

    /** 
     * Server timeout for read.
     *
     * Set our select timeout
     */
    struct timespec pselect_timeout;

    /**                                                                     
     * Signal masking.                                                      
     *                                                                      
     * This is our mask set in the constructor which is                     
     * required by pselect                                                  
     */                                                                     
    sigset_t mask;                                                          
                                                             
    /**                                                                     
    * Original signal masking.                                             
    *                                                                      
    * The original mask before it is changed is store                      
    * in this variable                                                     
    */                                                                     
    sigset_t origmask;                                                      

    /**
     * Selected socket file handle.
     *
     * Our read select fd
     */
    fd_set select_read;

    // Set the port and initialize our server and client variables
    Server(unsigned int port);
    
    //Creates a read select
    int wait();

    // Sets the number of bytes read
    void setNumberOfBytesInBuffer(size_t);

public:
    
    // Get the @socketfd
    int getSocketfd();

    // Get the @buffer byte value
    unsigned char getBufferByte(const unsigned int index) const;
    unsigned char operator[](const unsigned int index) const;

    // Get the port value
    unsigned int getPort();
	
    // Returns the number of bytes read
    size_t size();
    
    // Set our timeout value
    void setTimeout(
	    const unsigned int seconds, 
	    const unsigned int miliseconds = 0
	);

    // addTo a queue variable
    void appendBufferTo(std::queue<unsigned char> * q);
    
    // Read from the client
    virtual void process() = 0;
    virtual bool read() = 0;

    // Write back to our client
    virtual bool write(const char *) = 0;
    
    // An empty virtual desructor
    virtual ~Server();
};

#endif
