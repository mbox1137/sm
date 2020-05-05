#!/bin/bash
#WordReplace
echo ./wr.sh - revert
echo ./we.sh word toword - context replacement

for file in $(find -name '*.bak')
do
	fn=$(basename $file .bak)
	echo $file '->' $fn
	mv $file $fn
done

if [ .$1 == . ]
then
	exit
fi

files=$(find . -type f -and -not \( -name '_.sh*' -or -name '*~' \) \
	|xargs grep -l $1)
for file in $files
do
	fn=$(basename $file)
	echo $fn "($1 -> $2)"
	sed -i.bak -e "s/$1/$2/g" $fn
done
