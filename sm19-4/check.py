#!/usr/bin/python3
import sys, os, time, builtins, shutil

import signal, subprocess

def print(*args, **kwargs):
    builtins.print("check:", *args, **kwargs)

if len(sys.argv) < 2:
    print("./check.py ./test.py /tmp aa bb cc")
    sys.exit()
args = list(sys.argv)
args.pop(0)
tmpdir=os.path.join(sys.argv[2],os.getcwd().split('/')[-1])
shutil.rmtree(tmpdir, ignore_errors=True)
os.mkdir(tmpdir)
#tmp=args.pop(1)
pnames=list(map(lambda x: os.path.join(tmpdir,x),args[2:]))
lname=os.path.join(tmpdir, "test.log")
log=open(lname,"w")
print(pnames)
for pname in pnames:
    os.mkfifo(pname, mode = 0o666)
print(args)
proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=log,
                        bufsize=1,
                        universal_newlines=True)
cpid=int(proc.stdout.readline())
print(f"CPID={cpid}")
proc.stdin.close()

pipes=list()
for pname in pnames:
    print(pname)
#    pipes.append(os.open(pname, os.O_NONBLOCK|os.O_WRONLY))
    pipes.append(open(pname, 'w'))

print("Pipes done")
time.sleep(1)

n=0
for pipe in pipes:
    for k in range(n+1):
        builtins.print(f"{k**2:15}", file=pipe)
    n+=1

for pipe in pipes:
    pipe.close()

print("SIGRT:")
for k in range(len(args)-2):
    sig=signal.SIGRTMIN+k
    print(sig)
    os.kill(cpid, sig)
    line=proc.stdout.readline()
    line=line.strip()
    print(f"line={line}")
    time.sleep(0.3)

print("SIGTERM:")
os.kill(cpid, signal.SIGTERM)
for k in range(len(args)-1):
    line = proc.stdout.readline().strip()
    print(line)
