#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define OFFSET 0

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0)
        return 1;

    off_t fsize = lseek(fd, OFFSET, SEEK_END); // file_size + 0

    if (fsize == -1)
    {
        close(fd);
        return 1;
    }

    double* data = (double*) mmap(NULL , fsize, PROT_READ, MAP_PRIVATE, fd, OFFSET);

    if (*data == -1)
    {
        close(fd);
        return 1;
    }

    double sum = 0;
    size_t quantity = fsize / sizeof(double);

    for (size_t i = 0; i < quantity; ++i)
        sum += data[i];

    printf("%lf\n", sum / quantity);

    munmap(data, fsize);
    close(fd);

    return 0;
}

/*
References:
https://www.opennet.ru/man.shtml?topic=lseek&category=2&russian=0
https://www.opennet.ru/man.shtml?topic=mmap&category=2&russian=0
*/
