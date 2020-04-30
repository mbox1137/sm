#!/usr/bin/python3
#https://github.com/bright-tools/varints
#https://www.devdungeon.com/content/working-binary-data-python#writefile

#1 ./test.py
#1 ./test.py <test.tst
#2 ./test.py <test.tst test.bin
#3 ./test.py test.bin 3000

import varints
import sys
import random

print("^D")
nums=list()
while(len(sys.argv)<3):
    s=sys.stdin.readline()
    if(len(s)==0):
        break
    s=s.strip()
    sl=s.split('#')
    if(len(sl)>0):
        s=sl[0]
    qq=list(map(int,s.split()))
    nums.extend(qq)

fn=None
if len(sys.argv)>1:
    fn=sys.argv[1]
if len(nums)==0:
    nums=[k for k in range(int(sys.argv[2]))]

print(f"sum({nums[:3]}...{nums[-3:]})={sum(nums)}")

#nums = [random.randint(0,1000) for _ in range(10)]
print(f"nums: {sys.getsizeof(nums)}")
var = varints.leb128s.encode( nums )
print(f"var: {type(var)}: {sys.getsizeof(var)}")
"""
for a_byte in var:
    print (bin(a_byte))
binary_file = open("test.txt", "wb")
binary_file.write(b'\x00')
binary_file.close()
"""
if fn:
    binary_file = open(sys.argv[1], "wb")
    binary_file.write(var)
    binary_file.close()
