#!/bin/bash

FILE=out.log
TMPF=tmp.log
function myrun {
	echo $@
	./solution $@
	( $1 ; $2 ) | $3 > $TMPF
	if ! cmp $FILE $TMPF
	then
		diff -y $FILE $TMPF
	fi
}

myrun ls pwd wc $FILE
myrun ls pwd cat $FILE
