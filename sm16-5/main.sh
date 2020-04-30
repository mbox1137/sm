#!/bin/bash
#./main 3 out.bin 4 2 4
./mainseek 3 out.bin 4 2 4
ls -la out.bin
hexdump -d out.bin
