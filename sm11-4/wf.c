#include <stdio.h>
#include <unistd.h>

#define NN 4096

struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int count;           //осталось символов в буф
    int ind;             //номер символа на выдачу
};

static unsigned char bufferout[NN];
struct FileWriteState statout={STDOUT_FILENO,bufferout,NN};
struct FileWriteState *stout=&statout;

static int myputbuff(int fd, int n)
{
    int res=0;

    asm(
    "   int     $0x80               "
        :"=a"(res)
        :"a"(4), "b"(fd), "c"(bufferout), "d"(n)
    );
    return(res);
}

void flush(struct FileWriteState *st)
{
    int n;
    if(st->count>0 && st->count<=NN)
        n=myputbuff(st->fd, st->count);
    st->ind=0;
    st->count=0;
}

void writechar(int ic, struct FileWriteState *st)
{
    if(st->count>=NN)
        flush(st);
    st->buf[st->ind++]=ic;
    st->count++;
}
