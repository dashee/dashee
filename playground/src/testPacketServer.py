#!/usr/bin/python

import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 2047
    
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
                   
numberOfBytes=0;
while True:
    numberOfBytes+=1
    data, addr = sock.recvfrom(1024)
    print numberOfBytes
