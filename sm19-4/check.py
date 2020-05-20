#!/usr/bin/python3
import sys, os, time, builtins
import signal, subprocess

def print(*args, **kwargs):
    builtins.print("check:", *args, **kwargs)

if len(sys.argv) < 2:
    print("./check.py ./test.py")
    sys.exit()
args = list(sys.argv)
args.pop(0)
proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        bufsize=1,
                        universal_newlines=True)
cpid=int(proc.stdout.readline())
print(f"CPID={cpid}")
#print(4,5,6, file=proc.stdin)
proc.stdin.close()
for sig in range(signal.SIGRTMIN, signal.SIGRTMIN+len(args)-1):
    os.kill(cpid, sig)
    print(sig)
    time.sleep(0.3)
print("SIGRT:")
for k in range(len(args)-1):
    line = proc.stdout.readline().strip()
    print(line)
print("SIGTERM:")
os.kill(cpid, signal.SIGTERM)
for k in range(len(args)-1):
    line = proc.stdout.readline().strip()
    print(line)
