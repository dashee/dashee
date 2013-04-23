#include "Server/UDP.h"

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

bool Server_UDP::read()
{
    memset(buffer, 0, sizeof(buffer));
    
    //Recieave from client        
    if (recvfrom(socketfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_in, (socklen_t *)&client_in_length) == -1)
    {
        perror("Recieving from client failed");
        return false;
    }
    return true;
}

bool Server_UDP::write(const char * message)
{
    //const char message[] = "Error: Invalid Range, number must be between 1-100\n";
    if (sendto(socketfd, message, BUFFER_SIZE, 0, (struct sockaddr *) &client_in, client_in_length) == -1)
        return false;

    return true;
}
