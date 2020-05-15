#!/bin/bash
#alias ll="ls -l"
#shopt -s expand_aliases

FILE=/tmp/out.log
TMPF=/tmp/tmp.log
function myrun {
	echo $@
	./solution $@
	( $1 ; $2 ) | $3 > $TMPF
	if ! cmp $FILE $TMPF
	then
		diff -y $FILE $TMPF
	fi
}

myrun ./l1.sh pwd wc $FILE
myrun ./l1.sh pwd cat $FILE
myrun ./l1.sh ./ll.sh cat $FILE
myrun ./l1.sh ./ll.sh wc $FILE
