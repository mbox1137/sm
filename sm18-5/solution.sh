#!/bin/bash
#./solution 3 out.bin 4 2 4
CMD1="ls"
CMD2="cat"
CMD3="wc"
INF=in.tst
TMPF=tmp.txt
FILE=out.txt
function myrun {
	echo $@
	./solution $1 $2 $3 >$FILE
	$1 |$2 |$3 >$TMPF
	cmp $FILE $TMPF
}

myrun $CMD1 $CMD2 $CMD3

