#!/usr/bin/python3
#https://www.tutorialspoint.com/How-to-create-and-use-a-named-pipe-in-Python

import os, sys
fifo = "/tmp/hourly"
if not os.path.exists(fifo): os.mkfifo(fifo)
#fifo = open(path, mode='w', buffering=1)
inp = os.open(fifo, os.O_NONBLOCK | os.O_RDONLY)
out = os.open(fifo, os.O_NONBLOCK | os.O_WRONLY)
os.write(out, f"{123:15}\n".encode())
os.write(out, f"{456:15}\n".encode())
while True:
    try:
        str=os.read(inp, 16)
    except BlockingIOError:
        break
    print(str)
