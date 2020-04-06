#!/bin/bash
cat main.tst |./test.py main.bin
cat main.bin |hexdump -C
./main main.bin
