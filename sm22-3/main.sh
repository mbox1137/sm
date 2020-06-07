#!/bin/bash

(echo {1..4} && echo {5..6}) >main.dat
./sum.py <main.dat
./main 3 <main.dat

(echo {1..44} && echo {5..6}) >main.dat
./sum.py <main.dat
./main 3 <main.dat

