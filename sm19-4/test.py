#!/usr/bin/python3
#https://stackabuse.com/handling-unix-signals-in-python/

import os, sys, builtins, time
import signal

def print(*args, **kwargs):
    builtins.print(*args, **kwargs)
    sys.stdout.flush()
#    time.sleep(0.1)

def getnum():
    while 1:
        s=sys.stdin.readline()
        if len(s)==0: break
        s=s.strip()
        sl=s.split()
        for s in sl:
            yield int(s)**2

work = True
rtsig = -1

def receiveSignal(sig, frame):
    global work, rtsig
#    print('Received:', sig)
    rtsig = -1
    if sig == signal.SIGTERM:
        work=False
    else:
        smi=signal.SIGRTMIN
        sma=signal.SIGRTMIN+20
        rtsig=sig-smi if sig>=smi and sig<sma else -1
#    print(f"rtsig={rtsig}")
#    raise SystemExit('Exiting')
    return

def pipesum(pipename):
    s=0
    return s

def main():
    global work, rtsig
    print(os.getpid())
    args=list(sys.argv)
    args.pop(0)
    signal.signal(signal.SIGTERM, receiveSignal)
    for sig in range(signal.SIGRTMIN, signal.SIGRTMIN+20):
        signal.signal(sig, receiveSignal)
    while work:
        if rtsig>=0:
#            print(f"rtsig={rtsig}")
            print(pipesum(args[rtsig]))
            rtsig=-1
        signal.pause()
    for pname in args:
        print(pipesum(pname))

if __name__ == '__main__':
    main()
