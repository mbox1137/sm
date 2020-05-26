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
    int *data;
    size_t i;

    void *addr;

    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
        return 1;

    fsize = N * sizeof(int);

    addr = mmap(NULL , fsize, PROT_READ, MAP_SHARED, fd, 0);
    data = (int*) addr;

    if (data == NULL)
    {
        close(fd);
        return 1;
    }

    for(i = 0; i < N; ++i)
    {
        printf("%d\n", data[i]);
    }

    munmap(data, fsize);
    close(fd);

    return 0;
}

