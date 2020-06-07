#!/bin/bash

function myrun
{
	echo $1 $2
	echo $1 |./sum.py
	echo $1 |./main $2
	echo
}

#myrun "{1..4}" 3

(echo {1..4} && echo {5..6}) >main.dat
./sum.py <main.dat
./main 3 <main.dat

(echo {1..44} && echo {5..6}) >main.dat
./sum.py <main.dat
./main 3 <main.dat

echo {1..9999} >main.dat
./sum.py <main.dat
./main 500 <main.dat

