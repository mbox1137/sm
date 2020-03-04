#include <stdio.h>
#include <unistd.h>

#define NN 4096

struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    int count;           //осталось символов в буф
    int ind;             //номер символа на выдачу
};

static unsigned char bufferin[NN];
struct FileReadState statin={STDIN_FILENO,bufferin,NN,0};
struct FileReadState *stin=&statin;

//Ввод
static int mygetbuff(int fd)
{
    int res=0;

    asm(
    "   int     $0x80           \n\t"
        :"=a"(res)
        :"a"(3), "b"(fd), "c"(bufferin), "d"(NN)
    );
    return(res);
}

static int nextchar_(struct FileReadState *st)
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

static int lastchar_(struct FileReadState *st)
{
    return st->lc;
}

int lastchar()
{
    return lastchar_(stin);
}
