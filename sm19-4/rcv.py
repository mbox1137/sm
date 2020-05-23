#!/usr/bin/python3
#https://stackabuse.com/handling-unix-signals-in-python/

import os, sys, builtins, time
import signal
from functools import partial

def print(*args, **kwargs):
    builtins.print("rcv:", *args, **kwargs)

fifoname="myfifo"
tmpname="/tmp"
tmpdir=os.path.join(tmpname,os.getcwd().split('/')[-1])
if not os.path.exists(tmpdir): os.makedirs(tmpdir, exist_ok=True)
pname=os.path.join(tmpdir,fifoname)
print(pname)
if not os.path.exists(pname):
    os.mkfifo(pname, mode = 0o666)

pipe=open(pname, 'r')

for s in pipe:
    print(s.rstrip())
