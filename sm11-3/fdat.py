#!/usr/bin/python
import sys
if len(sys.argv)<2:
    print("./fdat.py 5",file=sys.stderr)
    sys.exit(-1)
n=int(sys.argv[1])
print('a'*n)
