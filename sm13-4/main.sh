#!/bin/bash

if [ -x ./main ]
then
	./main 10 0
	./main 3 0777
	./main 10 0777
	./main 10 0666
	echo SUID
	./main 10 04000
	./main 10 04010
	./main 10 04001
	echo SGID
	./main 10 02000
	./main 10 02001
	echo Sticky
	./main 10 01000
	./main 10 01002
	./main 10 01001
	./main 10 01003
else
	echo "run make"
fi
