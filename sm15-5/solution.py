#!/usr/bin/python3
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
    cmds=' '.join(cmd)
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    with open(fn, "rb") as f:
        s = f.read(-1)
    sl=s.split(b'\n')
    if not sl[-1]:
        sl.pop(-1)
    if k1<1: k1=1
    slt=sl[k1-1:k2-1][::-1]
    rl=result.stdout.split(b'\n')
    if not rl[-1]:
        rl.pop(-1)
    rlt=rl
    if slt!=rlt:
        print(cmds+"\t"+str(sl)+f"[{k1}:{k2}][::-1]"+"="+str(slt)+" -> "+str(rl))
