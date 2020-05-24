#!/bin/bash

function myrun {
	echo ./main $@
	./main $@
	echo '$?='$?
	echo
}

myrun txt1.txt txt2.txt
