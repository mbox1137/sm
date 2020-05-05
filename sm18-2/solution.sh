#!/bin/bash
#./solution 3 out.bin 4 2 4
INF=in.tst
TMPF=tmp.txt
RESF=out.txt
function myrun {
	echo $@
	./solution $1 $2 >$RESF
	$1 |$2 >$TMPF
	cmp $RESF $TMPF
}

./solution <$INF >$RESF
<$INF >$TMPF python3 -c "import sys; print( sum(int(w) for l in sys.stdin for w in l.split()))"
cmp $RESF $TMPF
