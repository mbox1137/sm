#!/bin/bash
if [ .$1 == . ]
then
	echo $0 ..
	exit -1
fi
pushd $1
echo clean...
make clean &> /dev/null
popd
name=$(basename $0 .sh)
lname=${1}/${name}.log
find $1 -type f -not -path "*/.git/*"| xargs wc > $lname
echo --- >> $lname
find $1 -type f -not -path "*/.git/*"| wc -l >> $lname
tail ${lname}
