#!/bin/bash
#./main.sh >main.log 2>&1

echo tree:
time tree ~/BP/P/C/Andrew/ >/dev/null
echo ----
echo
echo ./main:
time ./main ~/BP/P/C/Andrew/ >/dev/null
