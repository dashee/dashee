/**
 * This program is desinged to open up the serial devices on ttyACM0
 * and send commands to the Pololu Maestro USB to Servo controller.
 *
 * It is responsible for running three functions, Error, Get and Set
 * Please refere to maestroGetError, maestroGetPosition and maestroSetTarget respectively
 *
 * More information on the board can be found @ http://www.pololu.com/docs/0J40/all
 *
 * @author Shahmir
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/**
 * This command will return the error number on the Pololu Maestro Board
 * The error number is made of two bytes. so the response needs to add the returned
 * bytes together.
 *
 * To get the error we have to write 0xA1 to the controller to set it into error mode
 * Then read the error
 *
 * @param int fd - The file descriptor to the device
 *
 * @returns int - The number that represents the Error. See Pololu documentation for error numbers
 */
int maestroGetError(int fd)
{
    unsigned char command[] = { 0xA1 };
    if (write(fd, command, sizeof(command)) == -1)
    {
        perror("error getting Error");
        return -1;
    }
    
    unsigned char response[2];
    if(read(fd,response,2) != 2)
    {
        perror("error reading");
        return -1;
    }
    
    //Helpfull for debugging
    //printf("Error first: %d\n", response[0]);
    //printf("Error secon: %d\n", response[1]);

    return response[0] + 256*response[1];
}

/**
 * This function is responsible for getting the current position of a servo
 * which is identified by its channel. To get the current position of a channel,
 * we first need to write 2 bytes to the Pololu board, where the first byte 0x90 
 * represents that we want to get the position, and the second byte represents the channel
 * Once the write has been done, we need to read. Read returns two bytes representing one number
 *
 * @param int fd - The file descriptor to the device
 * @param unsigned char channel - The channel number represented in 8 bit binary
 *
 * @returns int - The collation of two bytes as one single number.
 */
int maestroGetPosition(int fd, unsigned char channel)
{
    unsigned char command[] = {0x90, channel};
    if(write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }

    unsigned char response[2];
    if(read(fd,response,2) != 2)
    {
        perror("error reading");
        return -1;
    }

    return response[0] + 256*response[1];
}

/**
 * This function writes a new target to a given servo channel, To set a servo target
 * the Pololu board requires 4 byte command where:
 *  byte1 - 0x84 - Telling the board that we are sending it set command
 *  byte2 - unsigned char - Telling the board which channel to set,
 *  byte3-byte4 - The collation of the numbers represent the target, as 2 bits are required to reach bigger values
 *
 * Its worth reading more on the Pololu documentation about the target bitsetting as you require
 * bit shifting to provide a valid servo target command
 *
 * @param int fd - The file descriptor to the device
 * @param unsigned char channel - The channel number represented in 8 bit binary
 * @param unsigned short target - We can represent two bytes in a unsigned short target.
 *
 * @returns int - The collation of two bytes as one single number.
 */
int maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
    unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
    if (write(fd, command, sizeof(command)) == -1)
    {
        perror("error writing");
        return -1;
    }
    return 0;
}

/*
 * Open Device,
 * Clear errors if any
 * Get and print current position
 * Set and print current position given the last position
 *
 * @returns int - Returns -1 on error, otherwise 0 
 */
int main()
{
    // Open the Maestro's virtual COM port.
    const char * device = "/dev/ttyACM0";  // Linux
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        perror(device);
        return -1;
    }

    int error = maestroGetError(fd);
    printf("Error is %d.\n", error); 

    int position = maestroGetPosition(fd, 1);
    printf("Current position is %d.\n", position); 

    int target = (position < 6000) ? 7000 : 5000;
    printf("Setting target to %d (%d us).\n", target, target/4);
    maestroSetTarget(fd, 1, target);

    close(fd);
    return 0;
}
