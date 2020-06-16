#!/usr/bin/python3
import sys

while True:
    s=sys.stdin.readline()
    if len(s)==0: break
    for k in map(int,s.split()):
        print(k-1)
