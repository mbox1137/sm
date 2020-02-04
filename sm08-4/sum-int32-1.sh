#!/bin/bash

cmd='echo "1 2 3 4 5" |./sum-int32-1'
echo $cmd
bash -c "$cmd"

cmd='echo "10 2147483647" |./sum-int32-1'
echo $cmd
bash -c "$cmd"

cmd='echo "-10 -2147483648" |./sum-int32-1'
echo $cmd
bash -c "$cmd"
