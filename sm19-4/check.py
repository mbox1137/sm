#!/usr/bin/python3
import sys, os, time, builtins, shutil

import signal, subprocess

def print(*args, **kwargs):
    builtins.print("check:", *args, **kwargs)

if len(sys.argv) < 2:
    print("./check.py ./test.py")
    sys.exit()
args = list(sys.argv)
args.pop(0)
tmpdir=os.path.join(sys.argv[2],os.getcwd().split('/')[-1])
shutil.rmtree(tmpdir, ignore_errors=True)
os.mkdir(tmpdir)
tmp=args.pop(1)
pnames=list(map(lambda x: os.path.join(tmpdir,x),args[1:]))
print(pnames)
list(map(os.mkfifo, pnames))
pipes=list()
for pname in pnames:
    print(pname)
    pipes.append(os.open(pname, os.O_WRONLY|os.O_NONBLOCK))
#w = os.open( 'my_fifo', os.O_WRONLY )
#r = os.open( 'my_fifo', os.O_RDONLY )
for pipe in pipes:
    close(pipe)
sys.exit()

proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        bufsize=1,
                        universal_newlines=True)
cpid=int(proc.stdout.readline())
print(f"CPID={cpid}")
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
