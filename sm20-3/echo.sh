#!/bin/bash
echo server
./echos 5555 &
sleep 1
echo client
./echoc bb 5555 111 222 333
sleep 1
echo kill server
killall echos
