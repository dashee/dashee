#include <dashee/Server/UDP.h>

using namespace dashee;

/** 
 * Construct our server.
 *
 * Our constructor sends the port to our base class, Along with that it also
 * initialized our @p socketfd by calling socket. It then sets and initializes
 * our @p server_in variable given the port, and any interface. Once all is done, 
 * it binds our server to a port. Any errors, will throw an exception
 *
 * @param port The port the server will run on
 *
 * @throws ExceptionServer when socket call or bind call fails
 */
ServerUDP::ServerUDP(unsigned int port) : Server(port)
{
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0)
        throw ExceptionServer();
    
    server_in.sin_family = AF_INET; //IPV4
    server_in.sin_port = htons(port);
    server_in.sin_addr.s_addr = htons(INADDR_ANY); //Any interfacea
    
    //Bind, Note the second parameter needs to be a sockaddr
    if (bind(socketfd, (struct sockaddr *) &server_in, sizeof(server_in)) == -1)
        throw ExceptionServer();
}

/**
 * Read from the client.
 *
 * Our wrapper to the recvfrom function, This is designed to set our buffer to null
 * and then do a recvfrom give the socket. The recvfrom will set our @p client_in variable
 * so it can be used to write data back to the client
 *
 * @throws ExceptionServer - When recvfrom comes back with an error 
 *
 * @returns always true
 * @retval TRUE always returned
 */
bool ServerUDP::read()
{
    memset(buffer, 0, sizeof(buffer));
    this->setNumberOfBytesInBuffer(0);
    
    ssize_t numberOfBytesInBuffer = recvfrom(
            socketfd, 
            buffer, 
            SERVER_BUFFER_SIZE, 
            0, 
            (struct sockaddr *)&client_in, 
            (socklen_t *)&client_in_length
        );

    //Recieave from client        
    if (numberOfBytesInBuffer == -1)
        throw ExceptionServer();

    this->setNumberOfBytesInBuffer((size_t)numberOfBytesInBuffer);
    return true;
}

/**
 * Read from the client, with a timeout set.
 *
 * This function is a wrapper around read(), but it calls Server::wait()
 * which is a wrapper around systems select() function. This function
 * allows us to have a timout if nothing came in our socket.
 * Note se have to setTimeout every time, as system select() modifes
 * the timestructure value. 0 value will set the timeout to nothing, 
 * so select will be instantanious.
 *
 * @param seconds Number of seconds to timeout
 * @param miliseconds Number of miliseconds to timeout
 *
 * @throws ExceptionServer If read fails
 * @throws ExceptionServerSignal If select timesout, or signal is intercepted
 *
 * @returns Boolean indicating read status
 * @retval TRUE if there was something read
 * @retval FALSE if there was nothing read
 */ 
bool ServerUDP::read(const unsigned int seconds, const unsigned int miliseconds)
{
    setTimeout(seconds, miliseconds);

    int select_return = wait();
    
    if (select_return > 0 && FD_ISSET(socketfd, &select_read))
    {
        read();
        return true;
    }
    else if (select_return == -1)
    {
        // If the errno is set to EINTR, that means
        // A signal went off in wait(), so throw an exception
        // Which can be caught correctly by our main program
        if (errno == EINTR) 
            throw ExceptionServerSignal();

        // Throw an exception so the main can set error
        throw ExceptionServer("ServerUDP::read failed with -1.");
    }

    return false;
}

/** 
 * Write to the client.
 *
 * This function will write to the client, Note that you need to get atleast
 * one read, before you can send to client, as it wont know where it is going
 * 
 * @param message The message to send
 *
 * @throws ExceptionServer If write fails
 */
bool ServerUDP::write(const char * message)
{
    //const char message[] = "Error: Invalid Range, number must be between 1-100\n";
    if (sendto(socketfd, message, strlen(message), 0, (struct sockaddr *) &client_in, client_in_length) == -1)
        throw ExceptionServer("Write failed with -1.");

    return true;
}
