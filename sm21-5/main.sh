#!/bin/bash

pushd ~
echo "Waiting for 1 Sec..."
~/BP/P/C/Andrew/cod/sm21-5/main find "2+2*2" 999 |head; echo $?
popd
echo
echo "Waiting for 1 Sec..."
~/BP/P/C/Andrew/cod/sm21-5/main find "2+2*2" 999 |head; echo $?
