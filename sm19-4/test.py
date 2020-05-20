#!/usr/bin/python3
#https://stackabuse.com/handling-unix-signals-in-python/
import os, sys, builtins, time
import signal

def print(*args, **kwargs):
    builtins.print(*args, **kwargs)
    sys.stdout.flush()
#    time.sleep(0.1)

def getnum():
    while 1:
        s=sys.stdin.readline()
        if len(s)==0: break
        s=s.strip()
        sl=s.split()
        for s in sl:
            yield int(s)**2

print(os.getpid())

for w in getnum():
    print(w)
