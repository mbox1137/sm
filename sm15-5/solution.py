#!/usr/bin/python
#https://defuse.ca/big-number-calculator.htm
#./solution file.txt 4 5
import sys, os, subprocess, glob
import itertools
if len(sys.argv) == 1:
    fl=glob.glob("f*.txt")
else:
    fl=[sys.argv[1]]
kl=list()
with open("t.txt") as t:
    while(True):
        s=t.readline()
        if(len(s)==0):
            break
        s=s.strip()
        sl=s.split('#')
        if(len(sl)>0):
            s=sl[0]
        sl=s.split()
        if(len(sl)==2):
            kl.append(list(map(int,sl)))
for fn,(k1,k2) in itertools.product(fl,kl):
    cmd=["./solution", fn, str(k1), str(k2)]
    with open(fn, "rb") as f:
        s = f.read(-1)
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    cmds=' '.join(cmd[0:2])+"\t"+' '.join(cmd[2:])
    sl=s.split(b'\n')
    if k1<1: k1=1
    slt=sl[k1-1:k2-1][::-1]
    slt.append(b'')
    rl=result.stdout.split(b'\n')
    if slt!=rl:
        print(cmds+"\t"+str(sl)+f"[{k1}:{k2}][::-1]"+"="+str(slt)+" -> "+str(rl))
