#!/bin/bash

function myrun {
	cmd="echo $1 | ./main"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "4 1 2 3 4"
myrun "9 1 2 3 4 5 6 7 8 9"
