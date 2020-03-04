#include <stdio.h>
#include <unistd.h>
#include "lnwf.h"

//https://stackoverflow.com/questions/52525630/define-in-inline-assembly-in-gcc
#define NN 4096
#define STR(x) #x
#define XSTR(s) STR(s)

static unsigned char bufferin[NN];
struct FileReadState statin={STDIN_FILENO,bufferin,NN,0};
struct FileReadState *stin=&statin;

//Ввод
/*
int mygetbuff(int fd)
{
    int res=0;

    asm(
    "   mov     $3, %%eax       \n\t"
    "   mov     %2, %%ebx       \n\t"
    "   lea     %1, %%ecx       \n\t"
    "   mov     $" XSTR(NN) ", %%edx    \n\t"
    "   int     $0x80           \n\t"
    "   mov     %%eax, %0       \n\t"
        :"=m"(res)
        :"m"(bufferin), "m"(fd)
//        :"b"(fd), "c"(bufferout), "d"(NN)
        :"eax","ebx","ecx","edx");
    return(res);
}
*/
int mygetbuff(int fd)
{
    int res=0;

    asm(
    "   int     $0x80           \n\t"
        :"=a"(res)
        :"a"(3), "b"(fd), "c"(bufferin), "d"(NN)
    );
    return(res);
}

int nextchar_(struct FileReadState *st)
{
    int ic;
    int temp_res;
    if (st->lc == -1)
        return -1;

    if (st->count == 0)
    {
        //чтение очередных данных
        temp_res = mygetbuff(st->fd);
        st->ind = 0;
        st->count = temp_res;
    }

    if (st->count == 0)
    {
        ic = -1;
    } else
    {
        ic = bufferin[st->ind];
        st->ind++;
        st->count--;
    }

    st->lc = ic;
    return ic;
}
int nextchar()
{
    return nextchar_(stin);
}

int lastchar_(struct FileReadState *st)
{
    return st->lc;
}
int lastchar()
{
    return lastchar_(stin);
}

//Вывод

static unsigned char bufferout[NN];
struct FileWriteState statout={STDOUT_FILENO,bufferout,NN};
struct FileWriteState *stout=&statout;

int myputbuff(int fd, int n)
{
    int res=0;

    asm(
    "	int	$0x80		    "
        :"=a"(res)
        :"a"(4), "b"(fd), "c"(bufferout), "d"(n)
    );
    return(res);
}

void flush_(struct FileWriteState *st)
{
    int n;
    if(st->count>0 && st->count<=NN) {
        n=myputbuff(st->fd, st->count);
    }
    st->ind=0;
    st->count=0;
}

void writechar_(struct FileWriteState *st, int ic)
{
    if(st->count>=NN) {
        flush_(st);
    }
    st->buf[st->ind++]=ic;
    st->count++;
}

void writechar(int ic)
{
    writechar_(stout, ic);
}

void flush(void)
{
    flush_(stout);
}

void myputchar(int ic)
{
    asm(
    "	mov	$4, %%eax	\n\t"
    "	mov	$1, %%ebx	\n\t"
    "	lea	%1, %%ecx	\n\t"
    "	mov	$1, %%edx	\n\t"
    "	int	$0x80		    "
        :"=m"(ic)
        :"m"(ic)
        :"eax","ebx","ecx","edx");

    return;
}

//Выход

void myexit(int ret_val)
{
    asm(
    "	movl	$1, %%eax	\n\t"
    "	movl	%1, %%ebx	\n\t"
    "	int	$0x80		    "
        :"=m"(ret_val)
        :"m"(ret_val)
        :"eax","ebx");

    return;
}
