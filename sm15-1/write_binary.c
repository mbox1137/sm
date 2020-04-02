#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define OFFSET 0

int main(int argc, char* argv[])
{

    if (argc != 2)
        return 1;

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0600);

    if (fd < 0)
        return 1;

    off_t fsize = lseek(fd, 100 * sizeof(double), SEEK_SET);

    if (fsize == -1)
    {
        close(fd);
        return 1;
    }

    int temp = write(fd, "", 1);

    double* data = (double*) mmap(NULL , fsize, PROT_WRITE, MAP_SHARED, fd, OFFSET);

    if (*data == -1)
    {
        close(fd);
        return 1;
    }

    for(size_t i = 0; i < 100; ++i)
    {
        data[i] = i;
    }

    munmap(data, fsize);
    close(fd);

    return 0;
}

/*
References:
https://www.opennet.ru/man.shtml?topic=lseek&category=2&russian=0
https://www.opennet.ru/man.shtml?topic=mmap&category=2&russian=0
*/
