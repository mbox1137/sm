#!/bin/bash

function myrun {
	echo -e "$1"
	bash -c "$1"
	echo
}

myrun "echo 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 |./main 4"
myrun "./main"
myrun "./main -9"
