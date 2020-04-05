#!/bin/bash
cat sm15-4.tst |./test.py test.bin
cat test.bin |hexdump -C
