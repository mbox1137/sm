#!/usr/bin/python3
import sys
import signal, subprocess

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
print(4,5,6, file=proc.stdin)
proc.stdin.close()
for line in proc.stdout:
#    print(line.decode("utf-8").strip())
    print(line.strip())
