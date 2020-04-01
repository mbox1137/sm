#!/usr/bin/python
#https://defuse.ca/big-number-calculator.htm
#./solution file.txt 4 5
import sys, os, glob
import itertools
if len(sys.argv) == 1:
    fl=glob.glob("f?.txt")
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
    cmd=f"./solution {fn} {k1} {k2}"
    print(cmd)
    os.system(cmd)
