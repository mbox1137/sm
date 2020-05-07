#!/bin/bash
#./main 3 out.bin 4 2 4
TMPF=tmp.txt
function myrun {
	echo $@
	./prog $1 $2 $3
#	$1 <$2 >$TMPF
#	cmp $3 $TMPF
}

myrun ls "ls -la" true
