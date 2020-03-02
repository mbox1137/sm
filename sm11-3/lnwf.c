#include <stdio.h>

#define NN 4096

struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    // здесь потребуется добавить поля для реализации буферизованного чтения
};

static unsigned char bufferin[NN];
struct FileReadState statin={0,bufferin,NN,0};
struct FileReadState *stin=&statin;

//Ввод

int nextchar(struct FileReadState *st)
{
    return(-1);
}

int lastchar(struct FileReadState *st)
{
    return(-1);
}

int mygetbuff(void)
{
    int ic=0, res=0;
    asm(
    "	mov	$3, %%eax	\n\t"
    "	mov	$0, %%ebx	\n\t"
    "	lea	%1, %%ecx	\n\t"
    " 	mov	$1, %%edx	\n\t"
    "	int	$0x80		\n\t"
    "	mov	%%eax, %0	\n\t"
        :"=m"(res)
        :"m"(ic)
        :"eax","ebx","ecx","edx");
    return(res);
}

//Вывод

struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    // здесь потребуется добавить поля для реализации буферизованной записи
};

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

//Проверка

int main(int argc, char **argv)
{
    int ic;
    while(1)
    {
        ic=nextchar(stin);
        if(ic==EOF)
            break;
        writechar(stout, ic);
    }
    return(0);
}

void _start(void)
{
    int retval;
    retval=main(0,0);
    myexit(retval);
}
