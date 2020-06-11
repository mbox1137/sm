#!/usr/bin/python

import sys

vals=dict()
NN=100
NI=1000
for k in range(NN*NI):
    vals[k]=0
while True:
    str=sys.stdin.readline()
    if(len(str)==0):
        break;
    vals[int(str)]+=1;
for val, count in vals.items():
    if count==1:
        continue
    print(val, count)
