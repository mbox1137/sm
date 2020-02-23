#!/bin/bash

function myrun {
	echo -e "$1"
	bash -c "$1"
	echo
}

myrun "echo abc25z |./main"
