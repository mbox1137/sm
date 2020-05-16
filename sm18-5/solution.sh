#!/bin/bash
#./solution 3 out.bin 4 2 4
#./solution ls$(printf ' cat%.0s' {1..100})
INF=in.tst
TMPF=tmp.log
FILE=out.log
function myrun {
	echo -n "./solution $@; "
	truncate -s 0 $FILE
	truncate -s 0 $TMPF
	tee stdin.log |./solution $@ >$FILE
	retval=$?
	if [ .$1 == . ]
	then
		echo "	Ok ($retval)"
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
			echo "	Ok ($retval)"
		else
			echo
			echo main:			pipe:
			echo --------------------------------------
			diff -y $FILE $TMPF
		fi
	fi
}

myrun ls cat cat wc	</dev/null
myrun ls cat wc		</dev/null
myrun ls cat		</dev/null
myrun ls		</dev/null
myrun			</dev/null
find .. |myrun wc
myrun ls$(printf ' cat%.0s' {1..100})	</dev/null
myrun ls qq		</dev/null
