#!/bin/bash
./test.py test.bin
cat test.bin |hexdump -C
