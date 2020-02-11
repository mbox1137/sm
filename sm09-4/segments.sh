#!/bin/bash

function myrun {
	cmd="echo $1 | ./main"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "10 20 15 25"
