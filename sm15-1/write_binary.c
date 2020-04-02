#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define OFFSET 0
#define N 10

int main(int argc, char* argv[])
{
    int fd, temp;
    off_t fsize;
    double *data;
    size_t i;
    double x;

    void *addr;

    if (argc != 2)
        return 1;

    x=255.0;

    fd = creat(argv[1], 0666);
    fsize = N * sizeof(double);
    lseek(fd, fsize - sizeof(double), SEEK_SET);
    write(fd,&x,sizeof(double));
    close(fd);

//------------------------------------------------

    fd = open(argv[1], O_RDWR);

    if (fd < 0)
        return 1;

    addr = mmap(NULL , fsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    data = (double*) addr;

    if (data == NULL)
    {
        close(fd);
        return 1;
    }

    for(i = 0; i < N; ++i)
    {
        data[i] = (double)i/10;
    }

    munmap(data, fsize);
    close(fd);

//------------------------------------------------

    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
        return 1;

    addr = mmap(NULL , fsize, PROT_READ, MAP_SHARED, fd, 0);
    data = (double*) addr;

    if (data == NULL)
    {
        close(fd);
        return 1;
    }

    for(i = 0; i < N; ++i)
    {
        printf("%a (%lg)\n", data[i], data[i]);
    }

    munmap(data, fsize);
    close(fd);

    return 0;
}

/*
References:
https://www.opennet.ru/man.shtml?topic=lseek&category=2&russian=0
https://www.opennet.ru/man.shtml?topic=mmap&category=2&russian=0
https://stackoverflow.com/questions/26259421/use-mmap-in-c-to-write-into-memory
*/
