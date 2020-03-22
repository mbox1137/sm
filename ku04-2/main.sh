#!/bin/bash
#https://defuse.ca/big-number-calculator.htm
./main
./main 1 2 3 4
./main 16 16 2 3
./main -1 1 -1 1
./main -10 1 -5 4
./main -10 5 4 5
echo 671 088 639:
./main 2147483647 2147483647 2 3
echo 2 281 701 374:
./main 2147483647 2147483647 8 9
./main 2147483647 2147483647 16 18
./main 2147483647 2147483647 32 36
