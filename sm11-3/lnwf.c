#include <stdio.h>
#include "lnwf.h"

#define NN 4096

static unsigned char bufferin[NN];
struct FileReadState statin={0,bufferin,NN,0};
struct FileReadState *stin=&statin;

//Ввод

int mygetbuff(int fd)
{
    int res=0;

    asm(
    "   mov     $3, %%eax       \n\t"
    "   mov     %2, %%ebx       \n\t"
    "   lea     %1, %%ecx       \n\t"
    "   mov     $4096, %%edx    \n\t"
    "   int     $0x80           \n\t"
    "   mov     %%eax, %0       \n\t"
        :"=m"(res)
        :"m"(bufferin), "m"(fd)
        :"eax","ebx","ecx","edx");
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
struct FileWriteState statout={1,bufferout,NN};
struct FileWriteState *stout=&statout;

void writechar(struct FileWriteState *st, int ic)
{
}

void flush(struct FileWriteState *st)
{
}

void myputbuff(int ic)
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
