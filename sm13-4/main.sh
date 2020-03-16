#!/bin/bash

if [ -x ./main ]
then
	./main 9 0
	./main 2 0777
	./main 9 0777
	./main 9 0666
	./main 9 04666
	./main 9 04777
	./main 9 02666
	./main 9 02777
	./main 9 01666
	./main 9 01777
else
	echo "run make"
fi
