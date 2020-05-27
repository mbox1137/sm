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
    int x;

    void *addr;

    if (argc != 2)
        return 1;

    x=255.0;

    fd = creat(argv[1], 0666);
    fsize = N * sizeof(int);
    lseek(fd, fsize - sizeof(int), SEEK_SET);
    write(fd,&x,sizeof(int));
    close(fd);

//------------------------------------------------

    fd = open(argv[1], O_RDWR);

    if (fd < 0)
        return 1;

    addr = mmap(NULL , fsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    data = (int*) addr;

    if (data == NULL)
    {
        close(fd);
        return 1;
    }

/*    for(i = 0; i < N; ++i)
    {
        data[i] = i;
    }
*/
    munmap(data, fsize);
    close(fd);

//------------------------------------------------

    return 0;
}

