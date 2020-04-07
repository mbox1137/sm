#!/bin/bash
args="*.txt ne.txt"
echo -e "\t./main $args"
./main $args
echo
echo -e "nl  w len\twc $args"
wc $args
