#include <dashee/Server.h>

using namespace dashee;

/**
 * Constructor.
 *
 * This function will initialize the @p port value which is passed as a parameter
 * it will also set the Server::client_in_length value to be the sizeof Server::client_in 
 * and set the server_in to have all 0's as its value.
 *
 * @param port The value of the port
 *
 * @throws ExceptionServer
 */
Server::Server(unsigned int port)
{
    this->port = port;
    this->numberOfBytesInBuffer = 0;
    
    client_in_length = sizeof(client_in);

    // 0 our server_in variable
    memset((char *) &server_in, 0, sizeof(server_in));

    // Initaize our mask variable as pselect will jump out on
    // SIGTERM
    memset((sigset_t *)&mask, 0, sizeof(mask));
    sigemptyset (&mask);
    sigaddset (&mask, SIGINT|SIGTERM);

    if (sigprocmask(SIG_BLOCK, &mask, &origmask) < 0)
        throw ExceptionServer();
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
 * Get the byte set in the buffer.
 *
 * The index specified the byte which is set in the buffer.
 * If the index is greater than or equal to the numberOfBytesInBuffer
 * an OutOfBound exception is thrown
 *
 * @param index The index value to get
 *
 * @throws ExceptionOutOfBounds();
 *
 * @returns The character which is set in the buffer
 */
unsigned char Server::getBufferByte(const unsigned int index) const
{
    if (index >= numberOfBytesInBuffer)
        throw ExceptionOutOfBounds("Trying to access an unset buffer");

    return buffer[index];
}

/**
 * Operator to facilitate getBufferByte() function.
 *
 * @param index The index value to get
 *
 * @returns The character
 */
unsigned char Server::operator[](const unsigned int index) const
{
    return this->getBufferByte(index);
}

/**
 * Get the current port.
 *
 * @returns The port number
 */
unsigned int Server::getPort()
{
    return this->port;
}

/**
 * Set the number of bytes read() from the command.
 * 
 * The value should always be greater or equall to 0
 *
 * @param numberOfBytesInBuffer The number of bytes which are returned from recvfrom
 *                in read() function
 *
 * @throws Exception if parameter value is not valid
 */
void Server::setNumberOfBytesInBuffer(size_t numberOfBytesInBuffer)
{
    if (numberOfBytesInBuffer < 0)
        throw Exception("The number of bytes must be positive");

    this->numberOfBytesInBuffer = numberOfBytesInBuffer;

}

/**
 * Returns the size of bytes in the buffer.
 *
 * Usefull for looping through the objects buffer.
 *
 * @returns Number representing the size of bytes
 */ 
size_t Server::size()
{
    return numberOfBytesInBuffer;
}

/**
 * Set timeout values.
 *
 * This function will set our timeout value
 * Note if it is set to 0, then our select will never return.
 *
 * @param seconds Number of seconds to timeout
 * @param miliseconds Number of nanoseconds to timeout
 *
 * @throws ExceptionServer If the timeout value was more than 999
 */
void Server::setTimeout(const unsigned int seconds, const unsigned int miliseconds)
{
    if (miliseconds > 999)
        throw ExceptionServer("SetTimeout set to value that is not between 0-999");
        
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
