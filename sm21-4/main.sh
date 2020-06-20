#!/bin/bash

function myrun
{
	echo $@
	bash -c "$@"
	echo ----
}

myrun "echo 1 |./main bc bc"
myrun "echo 1 |./main ./p1 bc"
myrun "echo 1 |./main bc ./p2"
myrun "echo 4 |./main bc ./p2"
myrun "echo 1 |./main ./p1 ./p2"
myrun "echo 4 |./main ./p1 ./p2"
myrun "echo 1 2 3|./main ./p1 ./p2"
myrun "./main ./p1 ./p2 <main.tst"
myrun "echo 1 2 3 4 5|./main ./p1 ./p2"
