#!/bin/bash
#./solution 3 out.bin 4 2 4

function pf {
	if [ -r $1 ]
	then
		rm $1
	fi
	mkfifo $1
}

for pname in /tmp/pf{0..19}
	do
		echo $pname
	done

function myrun {
	echo ./solution $@
	./solution $@
	echo '$?='$?
	echo
}

