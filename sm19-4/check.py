#!/usr/bin/python3
import subprocess

args = ["ping","-c 3","www.ru"]
proc = subprocess.Popen(args, 
                        stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE)
 
#data = process.communicate()
for line in proc.stdout:
    print(line.decode("utf-8").strip())
