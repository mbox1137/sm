#!/usr/bin/python
#https://github.com/bright-tools/varints
#https://www.devdungeon.com/content/working-binary-data-python#writefile

import varints
import sys
import random

nums=list()
while(True):
    try:
        s=input()
    except EOFError:
        break
    nums.append(int(s))
print(nums)

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
if len(sys.argv)==2:
    binary_file = open(sys.argv[1], "wb")
    binary_file.write(var)
    binary_file.close()
