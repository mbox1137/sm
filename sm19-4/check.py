#!/usr/bin/python3
import sys
import subprocess

args = ["./test.py"]
proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        bufsize=1,
                        universal_newlines=True)
print(4,5,6, file=proc.stdin)
proc.stdin.close()
for line in proc.stdout:
#    print(line.decode("utf-8").strip())
    print(line.strip())
