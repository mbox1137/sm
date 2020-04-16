#!/bin/bash
echo {1..3000} |./test.py main.bin
./main main.bin
echo
cat main.tst |./test.py test.bin
cat test.bin |hexdump -C
./main test.bin
echo
dd if=/dev/zero of=zero.bin bs=4k count=4k
./main zero.bin
