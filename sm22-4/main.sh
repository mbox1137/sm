#!/bin/bash

function myrun
{
	cmd="echo $2 |./main $1"
	echo $cmd
	bash -c "$cmd"
	cmd="echo $2 |./main_poll_efd $1"
	echo $cmd
	bash -c "$cmd"
	echo --------------------------------
}

myrun 3 "1 2 4 3 5 6 9 2"
myrun 3 "-1 2 4 -3 5  6 -9 2"
