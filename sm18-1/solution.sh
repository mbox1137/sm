#!/bin/bash
#./solution 3 out.bin 4 2 4
TMPF=tmp.txt
RESF=out.txt
function myrun {
	echo $@
	./solution $1 $2 >$RESF
	$1 |$2 >$TMPF
	cmp $RESF $TMPF
}

myrun ls wc
