#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 1024

class Server
{

protected:
    int socketfd;
    int port;
    
    struct sockaddr_in server_in;
    struct sockaddr_in client_in;
    int client_in_length;

    char buffer[BUFFER_SIZE];
    
    Server(int port);

public:

    char * getBuffer()
    {
        return buffer;
    }

    virtual bool read() = 0;
    virtual bool write(const char *) = 0;
};
