#!/bin/bash

function myrun {
	cmd="echo $1 | ./main"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "3 1 1 1 2 2 2"
