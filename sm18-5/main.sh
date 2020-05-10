#!/bin/bash
#./solution 3 out.bin 4 2 4
INF=in.tst
TMPF=tmp.log
FILE=out.log
function myrun {
	echo -n ./main $@
	truncate -s 0 $FILE
	truncate -s 0 $TMPF
	tee stdin.log |./main $@ >$FILE
	if [ .$1 == . ]
	then
		echo "	Ok"
	else
		cmd="( $1"
		shift
		for c in $@
		do
			cmd="$cmd | $c"
		done
		cmd="$cmd ) 2>&1"
		cat stdin.log |bash -c "$cmd >$TMPF"
		if cmp $FILE $TMPF
		then
			echo "	Ok"
		else
			echo
			echo main:			pipe:
			echo --------------------------------------
			diff -y $FILE $TMPF
		fi
	fi
}

echo "" |myrun ls cat cat wc
echo "" |myrun ls cat wc
echo "" |myrun ls cat
echo "" |myrun ls
echo "" |myrun
find .. |myrun wc
