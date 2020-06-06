#!/usr/bin/python
import sys

sm=0
while True:
    s=sys.stdin.readline()
    if len(s)==0: break
    sm+=sum(map(int,s.split()))
print(sm)
