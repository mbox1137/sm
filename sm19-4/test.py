#!/usr/bin/python3
#https://stackabuse.com/handling-unix-signals-in-python/
#https://stackoverflow.com/questions/29576982/pipe-no-such-file-or-directory

import os, sys, builtins, time
import signal
from functools import partial

def print(*args, **kwargs):
    builtins.print(*args, **kwargs)
    sys.stdout.flush()

def err(*args, **kwargs):
    builtins.print(*args, **kwargs, file=sys.stderr)
    sys.stderr.flush()

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
    err('Received:', sig)
    rtsig = -1
    if sig == signal.SIGTERM:
        work=False
    else:
        smi=signal.SIGRTMIN
        sma=signal.SIGRTMIN+20
        rtsig=sig-smi if sig>=smi and sig<sma else -1
    err(f"rtsig={rtsig}")
#    raise SystemExit('Exiting')
    return

sums=dict()

def pipesum(pipe):
    global sums;
    err("pipesum...")
    if pipe in sums:
        s=sums[pipe]
    else:
        s=0
        for str in pipe:
            err(f"str={str}")
            str=str.strip()
            try:
                n=int(str)
            except ValueError:
                break
            err(f"n={n}")
            s+=n
        sums[pipe]=s
    err(f"s={s}")
    return s
    """
    for chunk in iter(partial(pipe.read, 16), b''):
        err(f"chunk={chunk}")
        str=chunk.decode("utf-8").strip()
        try:
            n=int(str)
        except ValueError:
            break
    return s
    """

def main():
    global work, rtsig

    builtins.print(os.getpid()); sys.stdout.flush()

    args=list(sys.argv)
    exe=args.pop(0)
    tmp=args.pop(0)
    tmpdir=os.path.join(tmp,os.getcwd().split('/')[-1])
    pnames=list(map(lambda x: os.path.join(tmpdir,x),args))
    signal.signal(signal.SIGTERM, receiveSignal)
    for sig in range(signal.SIGRTMIN, signal.SIGRTMIN+20):
        signal.signal(sig, receiveSignal)
    pipes=list();
    for pname in pnames:
#        pipes.append(os.open(pname, os.O_NONBLOCK | os.O_RDONLY))
        pipes.append(open(pname, "r"))
    err("Pipes done")
    while work:
        err(f"while work: rtsig={rtsig}")
        if rtsig>=0:
            err(f"pipesum({pipes[rtsig]})=...")
            s=pipesum(pipes[rtsig])
            err(f"pipesum={s}")
            print(s)
            rtsig=-1
        signal.pause()
    for pipe in pipes:
        print(pipesum(pipe))

if __name__ == '__main__':
    main()
