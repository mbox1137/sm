#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
work = True
rtsig = -1
sums=dict()
*/

/*
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
    return
*/
/*
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
*/
/*
def main():
    global work, rtsig

    builtins.print(os.getpid()); sys.stdout.flush()

    args=list(sys.argv)
    exe=args.pop(0)
    tmp=args.pop(0)
    """
    tmpdir=os.path.join(tmp,os.getcwd().split('/')[-1])
    pnames=list(map(lambda x: os.path.join(tmpdir,x),args))
    """
    pnames=list(args)
    signal.signal(signal.SIGTERM, receiveSignal)
    for sig in range(signal.SIGRTMIN, signal.SIGRTMIN+20):
        signal.signal(sig, receiveSignal)
    pipes=list();
    for pname in pnames:
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
*/

int main(int argc, char *argv[])
{
}
