#include <stdio.h>
#include <unistd.h>

#define NN 4096

/*
struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    int count;           //осталось символов в буф
    int ind;             //номер символа на выдачу
};
*/
struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int count;           //осталось символов в буф
    int ind;             //номер символа на выдачу
};
int nextchar();
int lastchar();
void myputchar(int ic);
void writechar(int c, struct FileWriteState *out);
void flush(struct FileWriteState *out);
void myexit(int ret_val);
struct FileReadState *stin;
struct FileWriteState *stout;

/*
static unsigned char bufferin[NN];
struct FileReadState statin={STDIN_FILENO,bufferin,NN,0};
struct FileReadState *stin=&statin;

//Ввод
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
*/
//Вывод

static unsigned char bufferout[NN];
struct FileWriteState statout={STDOUT_FILENO,bufferout,NN};
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

/*
void myputchar(int ic)
{
    asm volatile(
    "   mov     $4, %%eax       \n\t"
    "   mov     $1, %%ebx       \n\t"
    "   lea     %1, %%ecx       \n\t"
    "   mov     $1, %%edx       \n\t"
    "   int     $0x80               "
        :"=m"(ic)
        :"m"(ic)
        :"eax","ebx","ecx","edx");

    return;
}

//Выход

void myexit(int ret_val)
{
    asm(
    "   movl    $1, %%eax       \n\t"
    "   movl    %1, %%ebx       \n\t"
    "   int     $0x80               "
        :"=m"(ret_val)
        :"m"(ret_val)
        :"eax","ebx");

    return;
}
*/
