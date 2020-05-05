#!/bin/bash
#./solution 3 out.bin 4 2 4
CMD1="ls"
CMD2="ls -la"
CMD3="wc"
INF=in.tst
TMPF=tmp.txt
FILE=out.txt
function myrun {
	echo $@
	./solution $1 $2 >$FILE
	$1 |$2 >$TMPF
	cmp $FILE $TMPF
}

./solution $CMD1 $CMD2 $CMD3 $FILE
( $CMD1 ; $CMD2 ) | $CMD3 > $TMPF
cmp $FILE $TMPF
