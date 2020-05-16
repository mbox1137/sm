#!/bin/bash
#./solution 3 out.bin 4 2 4
function myrun {
	echo ./solution $@
	./solution $@
#	echo '$?='$?
#	echo
}

myrun 5
myrun 1
myrun 0
myrun
myrun -1
myrun qq
myrun 7 8
