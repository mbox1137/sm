#!/bin/bash

function myrun {
	./fdat.py "$1" >in.dat
	./main <in.dat >out.dat
	diff in.dat out.dat
	echo "$(if [ $?==0 ] ;then echo Ok ;else echo Fail ;fi): $(wc -c in.dat) $(wc -c out.dat)"
}

myrun "0"
myrun "5"
myrun "4093"
myrun "4094"
myrun "4095"
myrun "4096"
myrun "10000000"
