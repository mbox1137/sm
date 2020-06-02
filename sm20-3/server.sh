#!/bin/bash
./server 5001 >server.log &
./client.py 127.0.0.1 5001 1
./client.py 127.0.0.1 5001 2
./client.py 127.0.0.1 5001 3
./client.py 127.0.0.1 5001 0
cat server.log
