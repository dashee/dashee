#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include "Servo.h"

#define BUFFER_SIZE 1024

int main()
{
    Servo s("/dev/ttyACM0");
    int error = s.getError();
    if (error > 0)
        fprintf(stderr, "Servo Error: %d", error);

    int socketfd;
    int port = 2047;

    struct sockaddr_in server_in;
    struct sockaddr_in client_in;
    int client_in_length = sizeof(client_in);
    
    char buffer[BUFFER_SIZE];
    
    //Create a socket
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0)
    {
        perror("Creating a socket failed!");
        return -1;
    }
    
    // Set the server address, by defaulting server_in to 0
    // then setting it to the port, before binding
    memset((char *) &server_in, 0, sizeof(server_in));
    server_in.sin_family = AF_INET; //IPV4
    server_in.sin_port = htons(port);
    server_in.sin_addr.s_addr = htons(INADDR_ANY); //Any interface

    //Bind, Note the second parameter needs to be a sockaddr
    if (bind(socketfd, (struct sockaddr *) &server_in, sizeof(server_in)) == -1)
    {
        perror("Binding Failed, ec set to errno!");
        return -2; 
    }
    
    //Keep listening, for stuff
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        
        if (recvfrom(socketfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_in, (socklen_t *)&client_in_length) == -1)
        {
            perror("Recieving from client failed");
            return -3;
        }
        
        int target = atoi(buffer);
        printf("Set to: %d\n", target);

        if (target > 0 && target <= 100)
        {
            //int target = (s.getTarget(2) < 6000) ? 8000 : 992;
            //printf("Channel 1: %d\n", target);
            
            if (target == 1) 
                target = 992;
            else if (target == 100)
                target = 8000;
            else
                target = ((7008/100) * target) + 992;

            s.setTarget(1, target);

            printf("Channel 1: %d\n", target);
        }
        else
        {   
            const char message[] = "Error: Invalid Range, number must be between 1-100\n";
            if (sendto(socketfd, message, sizeof(message), 0, (struct sockaddr *) &client_in, client_in_length) == -1)
                perror("Sending to client failed");
        }
    
        //Make sure its not empty lines
        printf("Message: %s", buffer);
    }

    printf("Hello to the world of tomrow");
    return 0;
}
