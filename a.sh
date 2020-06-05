#!/bin/bash
# ../a.sh /tmp/a ../../PNG
for name in $(ls -1 $1)
do
	echo cp $1/$name $2/sm$name
	cp $1/$name $2/sm$name
done
