#!/bin/bash
echo {1..3000} |./test.py main.bin
./main main.bin
echo
cat main.tst |./test.py test.bin
cat test.bin |hexdump -C
./main test.bin
