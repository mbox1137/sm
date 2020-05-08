#!/bin/bash
#./main.sh >main.log 2>&1

echo tree ..
time tree .. >/dev/null
echo ----
echo
echo ./main ..
time ./main .. >/dev/null
echo ----
echo
echo ./main
./main; echo $?
echo ----
echo
echo ./main b
./main b; echo $?
