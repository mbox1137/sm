#!/bin/bash

wdir=$(pwd)
pushd ~
echo "Waiting for 1 Sec..."
$wdir/main find "2+2*2" 1000| head; echo $?
popd

echo
echo "Waiting for 1 Sec..."
./main find "2+2*2" 1000 | head; echo $?

echo
echo "Waiting for 1 Sec..."
./main ./sleep.sh "2+2*2" 1000 | head; echo $?

echo
echo "Waiting for 3 Sec..."
./main ./sleep.sh "2+2*2" 3000 | head; echo $?
