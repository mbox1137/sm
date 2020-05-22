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
tmp=args.pop(1)
pnames=list(map(lambda x: os.path.join(tmpdir,x),args[1:]))
print(pnames)
for pname in pnames:
    os.mkfifo(pname, mode = 0o666)
proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.STDOUT,
                        bufsize=1,
                        universal_newlines=True)
cpid=int(proc.stdout.readline())
print(f"CPID={cpid}")
proc.stdin.close()

time.sleep(1)

pipes=list()
for pname in pnames:
    print(pname)
#    pipes.append(os.open(pname, os.O_NONBLOCK|os.O_WRONLY))
    pipes.append(os.open(pname, os.O_WRONLY))

k=0
for pipe in pipes:
    os.write(pipe, f"{k:15}\n".encode())
    k+=1

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
