#!/bin/bash
#./main 3 out.bin 4 2 4
TMPF=tmp.txt
function myrun {
	echo $@
	./prog $1 $2 $3
	$1 <$2 >$TMPF
	cmp $3 $TMPF
}

./main
./main " qq ww ee rr tt yy "
./main "ls -la"
