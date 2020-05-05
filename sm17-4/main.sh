#!/bin/bash
#./main 3 out.bin 4 2 4
TMPF=tmp.txt
function myrun {
	echo $@
	./main $1 $2 $3
	$1 <$2 >$TMPF
	cmp $3 $TMPF
}
if [ ! -r /tmp/a/apb ]
then
	echo mkfifo /tmp/a/apb
	mkfifo /tmp/a/apb
fi
echo '/usr/bin/python3 </tmp/a/apb &'
/usr/bin/python3 </tmp/a/apb &
sleep 1
echo 'cat apb.py >/tmp/a/apb'
cat apb.py >/tmp/a/apb
sleep 1
echo "done"
