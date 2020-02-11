#!/usr/bin/python
# echo 10 20 15 25 | ./segments.py
#MAX(-MAX(a.min,b.min)+MIN (a.max,b.max),0)
amin, amax, bmin, bmax = map(int,input().split())
qq=max(-max(amin,bmin)+min(amax,bmax),0)
print(f"length(({amin}, {amax}) ^ ({bmin}, {bmax}))={qq}")
