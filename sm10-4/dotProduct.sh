#!/bin/bash

function myrun {
	cmd="echo $1 | ./main"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "4 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8"
