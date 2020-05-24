#!/usr/bin/python3
import sys, os, time, builtins, shutil

import signal, subprocess

def print(*args, **kwargs):
    builtins.print("snd:", *args, **kwargs)

fifoname="myfifo"
tmpname="/tmp"
tmpdir=os.path.join(tmpname,os.getcwd().split('/')[-1])
if not os.path.exists(tmpdir): os.makedirs(tmpdir, exist_ok=True)
pname=os.path.join(tmpdir,fifoname)
print(pname)
if not os.path.exists(pname): os.mkfifo(pname, 0o666)

pipe=open(pname, 'w')

k=0
for k in range(10):
    print(f"\"{k:15}\"", file=pipe)
