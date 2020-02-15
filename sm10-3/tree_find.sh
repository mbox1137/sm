#!/bin/bash

function myrun {
	cmd="echo $1 | ./main"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "3 4"
myrun "5 12"
myrun "-10 24"
