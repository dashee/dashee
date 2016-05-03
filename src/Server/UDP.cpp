#include <dashee/Server/UDP.h>

using namespace dashee;

/** 
 * Construct our server.
 *
 * Our constructor sends the port to our base class, Along with that it also
 * initialized our @p socketfd by calling socket. It then sets and initializes
 * our @p server_in variable given the port, and any interface. Once all is 
 * done, it binds our server to a port. Any errors, will throw an exception
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
    server_in.sin_addr.s_addr = htons(INADDR_ANY); //Any interface
#pragma GCC diagnostic pop
    
    //Bind, Note the second parameter needs to be a sockaddr
    if (
	    bind(
		socketfd, 
		reinterpret_cast<const struct sockaddr *>(&server_in), 
		sizeof(server_in)
	    ) == -1
	)
        throw ExceptionServer("Binding failed");

    // Initialize our mask variable as pselect will jump out on SIGTERM
    memset(static_cast<void *>(&mask), 0, sizeof(mask));
    sigemptyset (&mask);
    sigaddset (&mask, SIGINT|SIGTERM);

    if (sigprocmask(SIG_BLOCK, &mask, &origmask) < 0)
            throw ExceptionServer();
}

/**
 * Process from the client and store into buffer.
 *
 * Our wrapper to the recvfrom function, This is designed to set our buffer to 
 * null and then do a recvfrom give the socket. The recvfrom will set our @p 
 * client_in variable so it can be used to write data back to the client
 *
 * @throws ExceptionServer When recvfrom comes back with an error 
 *
 * @returns always true
 * @retval TRUE always returned
 */
void ServerUDP::process()
{
    memset(buffer, 0, sizeof(buffer));
    this->setNumberOfBytesInBuffer(0);
    
    ssize_t numberOfBytesInBuffer = recvfrom(
            socketfd, 
            buffer, 
            SERVER_BUFFER_SIZE, 
            0, 
            reinterpret_cast<struct sockaddr *>(&client_in), 
            static_cast<socklen_t *>(&client_in_length)
        );

    //Recieave from client        
    if (numberOfBytesInBuffer == -1)
        throw ExceptionServer();

    this->setNumberOfBytesInBuffer(static_cast<size_t>(numberOfBytesInBuffer));
}

/**
 * Read from the client, with a timeout set.
 *
 * First call wait, when wait breaks it tells us weather
 * it broke because of there was something to read or weather
 * nothing was there to read.
 *
 * If there was nothing to read we check errno to be EINTR to 
 * determine a timeout, otherwise something went very very wrong
 *
 * @returns Boolean indicating read status
 * @retval TRUE if there was something read
 * @retval FALSE if there was nothing read and it timed out
 * 
 * @throws ExceptionServer If read fails
 */ 
bool ServerUDP::read()
{
    // Wait and timeout
    int select_return = wait();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
    if (select_return > 0 && FD_ISSET(socketfd, &select_read))
    {
#pragma GCC diagnostic pop
	process();
	return true;
    }

    // Timeout
    else if (select_return == 0)
	return false;
    
    // If the errno is set to EINTR, that means
    // a signal went off
    else if (select_return == -1 && errno == EINTR)
	return false;
    else
        throw ExceptionServer("ServerUDP::read failed with -1.");
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
    if (
	    sendto(
		socketfd, 
		message, 
		strlen(message), 
		0, 
		reinterpret_cast<struct sockaddr *>(&client_in), 
		client_in_length
	    ) == -1
	)
        throw ExceptionServer("Write failed with -1.");

    return true;
}
