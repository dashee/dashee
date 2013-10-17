#!/bin/bash

hexdump -v -e '49/1 "%02x " "\n"' < $1
