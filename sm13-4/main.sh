#!/bin/bash

if [ -x ./main ]
then
	./main 3 0640
	./main 9 0640
else
	echo "run make"
fi
