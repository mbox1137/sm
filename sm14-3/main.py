#!/usr/bin/python
import sys
if(len(sys.argv)!=2):
    print("./main ~ |./main.py find.lst",file=sys.stderr)

def fd2l(fd):
    l= fd.read().splitlines()
    return(l)

mainl=fd2l(sys.stdin)
with open(sys.argv[1]) as fd:
    findl=fd2l(fd)
mains=set(mainl)
finds=set(findl)
print(len(mainl), len(mains))
print(len(findl), len(finds))
print(len(mains-finds))
print(len(finds-mains))
