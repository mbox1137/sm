#!/bin/bash
echo ----
cmd="echo -2 3 4 5 | ./abcd"
echo $cmd
bash -c "$cmd"
echo ----
cmd="echo -2 3 4 5 | ./tb"
echo $cmd
bash -c "$cmd"
echo ----
