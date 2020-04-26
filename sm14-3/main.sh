#!/bin/bash
#./main.sh >main.log 2>&1

echo tree:
time tree .. >/dev/null
echo ----
echo
echo ./main:
time ./main .. >/dev/null
