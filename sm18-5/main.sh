#!/bin/bash
#./solution 3 out.bin 4 2 4
INF=in.tst
TMPF=tmp.log
FILE=out.log
function myrun {
	echo ./main $@
	./main $@ >$FILE
	cmd="( $1"
	shift
	for c in $@
	do
		cmd="$cmd | $c"
	done
	cmd="$cmd ) 2>&1"
	bash -c "$cmd >$TMPF"
	if ! cmp $FILE $TMPF
	then
		echo main:	pipe:
		diff -y $FILE $TMPF
	fi
}

myrun ls cat wc
