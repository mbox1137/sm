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

def pipesum(pipe):
    s=0
    while True:
        try:
            str=os.read(pipe, 16)
        except BlockingIOError:
            break
        str=str.decode("utf-8").strip()
        if len(str)>0:
            sl=str.split()
            for str in sl:
                s+=int(str)
        else:
            break
    return s

def main():
    global work, rtsig
    print(os.getpid())
    args=list(sys.argv)
    exe=args.pop(0)
    tmp=args.pop(0)
    tmpdir=os.path.join(tmp,os.getcwd().split('/')[-1])
    pnames=list(map(lambda x: os.path.join(tmpdir,x),args))
    pipes=list();
    for pname in pnames:
        pipes.append(os.open(pname, os.O_NONBLOCK | os.O_RDONLY))
    signal.signal(signal.SIGTERM, receiveSignal)
    for sig in range(signal.SIGRTMIN, signal.SIGRTMIN+20):
        signal.signal(sig, receiveSignal)
    while work:
        if rtsig>=0:
#            print(f"rtsig={rtsig}")
            print(pipesum(pipes[rtsig]))
            rtsig=-1
        signal.pause()
    for pipe in pipes:
        print(pipesum(pipe))

if __name__ == '__main__':
    main()
