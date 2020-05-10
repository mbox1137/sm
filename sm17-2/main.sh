#!/bin/bash
#./main 3 out.bin 4 2 4
TMPF=tmp.txt
function myrun {
	echo $@
	./prog $1 $2 $3
	$1 <$2 >$TMPF
	cmp $3 $TMPF
}

./main "ls -la"
echo
./main "sleep 10" >main.log 2>&1 &
sleep 1
killall sleep
cat main.log


