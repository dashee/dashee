#include "UDP.h"

/** 
 * Our constructor sends the port to our base class, Along with that it also
 * initialized our @socketfd by calling socket. It then sets and initializes
 * our @server_in variable given the port, and any interface.
 *
 * Once all is done, it binds our server to a port.
 *
 * Any errors, will throw an exception
 *
 * @param (int)port - The port the server will run on
 *
 * @throw - Exception_Server - when socket call or bind call fails
 */
Server_UDP::Server_UDP(int port) : Server(port)
{
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0)
        throw Exception_Server();
    
    server_in.sin_family = AF_INET; //IPV4
    server_in.sin_port = htons(port);
    server_in.sin_addr.s_addr = htons(INADDR_ANY); //Any interfacea
    
    //Bind, Note the second parameter needs to be a sockaddr
    if (bind(socketfd, (struct sockaddr *) &server_in, sizeof(server_in)) == -1)
        throw Exception_Server();
}

/**
 * Our wrapper to the recvfrom function, This is designed to set our buffer to null
 * and then do a recvfrom give the socket. The recvfrom will set our @client_in variable
 * so it can be used to write data back to the client
 *
 * @throws Exception_Server - When recvfrom comes back with an error 
 *
 * @return bool - true always
 */
bool Server_UDP::read()
{
    memset(buffer, 0, sizeof(buffer));
    
    //Recieave from client        
    if (recvfrom(socketfd, buffer, SERVER_BUFFER_SIZE, 0, (struct sockaddr *) &client_in, (socklen_t *)&client_in_length) == -1)
        throw Exception_Server();
    return true;
}

/**
 * This function is a wrapper around @read(), but it calls @wait
 * which is a wrapper around systems select() function. This function
 * allows us to have a timout if nothing came in our socket.
 * Note se have to setTimeout every time, as system select() modifes
 * the timestructure value.
 *
 * 0 value will set the timeout to nothing, so select will be instantanious
 *
 * @param (long)seconds - Number of seconds to timeout
 * @param (long)nanoseconds - Number of nanoseconds to timeout
 *
 * @throws - Exception_Server - If write fails
 *
 * @returns bool - true, if there was something read. false on timeout
 */ 
bool Server_UDP::read(long seconds, long nanoseconds)
{
    setTimeout(seconds, nanoseconds);

    int select_return = wait();
    
    if (select_return > 0 && FD_ISSET(socketfd, &select_read))
    {
        return read();
    }
    else if (select_return == -1)
    {
        // If the errno is set to EINTR, that means
        // A signal went off in wait(), so throw an exception
        // Which can be caught correctly by our main program
        if (errno == EINTR) 
            throw Exception_Server_Signal();

        // Throw an exception so the main can set error
        throw Exception_Server("Server_UDP::read failed with -1.");
    }

    return false;
}

/** 
 * This function will write to the client, Note that you need to get atleast
 * one read, before you can send to client, as it wont know where it is going
 * 
 * @param (const char *)message - The message to send
 *
 * @throws - Exception_Server - If write fails
 */
bool Server_UDP::write(const char * message)
{
    //const char message[] = "Error: Invalid Range, number must be between 1-100\n";
    if (sendto(socketfd, message, strlen(message), 0, (struct sockaddr *) &client_in, client_in_length) == -1)
        throw Exception_Server("Write failed with -1.");

    return true;
}
