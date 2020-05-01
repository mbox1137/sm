#!/bin/bash
#./main 3 out.bin 4 2 4
TMPF=tmp.txt
function myrun {
	wc <in.txt >out.txt
	$1 <$2 >$TMPF
	cmp $3 $TMPF
}

myrun wc in.txt out.txt
