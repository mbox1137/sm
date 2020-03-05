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
static struct FileWriteState statout={STDOUT_FILENO,bufferout,NN,0,0};
struct FileWriteState *stout=&statout;

int myputbuff(int fd, int n)
{
    int res=0;

    asm(
    "   int     $0x80               "
        :"=a"(res)
        :"a"(4), "b"(fd), "c"(bufferout), "d"(n)
    );
    return(res);
}

void flush(struct FileWriteState *out)
{
    int n;
    if(out->count>0 && out->count<=NN)
        n=myputbuff(out->fd, out->count);
    out->ind=0;
    out->count=0;
}

void writechar(int c, struct FileWriteState *out)
{
    if(out->count>=NN)
        flush(out);
    out->buf[out->ind++]=c;
    out->count++;
}
