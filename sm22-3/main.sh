#!/bin/bash

(echo {1..4} && echo {5..6}) >main.dat
./sum.py <main.dat
./main  <main.dat
