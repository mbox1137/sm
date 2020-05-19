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
 
#data = process.communicate()
sys.stdout.write('1 2 3\n')
proc.stdin.write('1 2 3\n')
print(proc.stdin, 4,5,6)
proc.stdin.close()
for line in proc.stdout:
#    print(line.decode("utf-8").strip())
    print(line.strip())
