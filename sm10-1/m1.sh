#!/bin/bash

function myrun {
	cmd="echo $1 | ./main1"
	echo -e "$cmd \t $(bash -c "$cmd")"
}

myrun "10 15"
myrun "6000000000 10000000000"
