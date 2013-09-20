#!/usr/bin/python

import socket

UDP_IPADDR = "127.0.0.1"
UDP_PORT = 2047

byteArray = bytearray(2);
byteArray[0] = 17;
byteArray[1] = 33;

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);

x = 0
while True:
    client.sendto(byteArray, (UDP_IPADDR, UDP_PORT));
    x=x+1

    if x == 1000000:
        break
