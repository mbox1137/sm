#!/bin/bash
#./solution 3 out.bin 4 2 4
INF=in.tst
TMPF=tmp.txt
FILE=out.txt
function myrun {
	echo $@
	./solution $@ >$FILE
	cmd="( $1"
	shift
	for c in $@
	do
		cmd="$cmd | $c"
	done
	cmd="$cmd ) 2>&1"
	bash -c "$cmd >$TMPF"
	cmp $FILE $TMPF
}

myrun ls cat wc
