#!/usr/bin/python3
#https://www.tutorialspoint.com/How-to-create-and-use-a-named-pipe-in-Python
#echo -e "999999999999999\n123456789012345\n">/tmp/hourly

import os, sys
import math
from functools import partial

fifo = "/tmp/hourly"
if not os.path.exists(fifo): os.mkfifo(fifo)
inp = open(fifo, "rb", 0)
#out = open(fifo, "wb", 0)
print("----")
#with open('somefile', 'rb') as openfileobject:
for chunk in iter(partial(inp.read, 16), b''):
    print(f"chunk={chunk}")
    str=chunk.decode("utf-8").strip()
    print(f"str={str}")
    try:
        n=int(str)
    except ValueError:
        break
    print(f"log2({n})={math.log(n)/math.log(2)}")
