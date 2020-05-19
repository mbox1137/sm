#!/usr/bin/python3
#https://stackabuse.com/handling-unix-signals-in-python/
import os, sys
import signal

def getnum():
    while 1:
        s=sys.stdin.readline()
        if len(s)==0: break
        s=s.strip()
        sl=s.split()
        for s in sl:
            yield int(s)**2

for w in getnum():
    print(w)

print(f"PID={os.getpid()}")
