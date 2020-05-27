#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define SIZE sizeof(long long)

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(EXIT_FAILURE);

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
        exit(EXIT_FAILURE);

    size_t i, inx;
    long long num, min_num;

    int success = read(fd, &num, SIZE);

    if (success == 0)
    {
        close(fd);
        exit(EXIT_SUCCESS);
    }

    if (success != SIZE)
        exit(EXIT_FAILURE);

    min_num = num;
    inx = 0;

    for(i = 1; ; ++i)
    {
        if (read(fd, &num, SIZE) != SIZE)
            break;

        if (num < min_num)
        {
            min_num = num;
            inx = i;
        }
    }

    if (min_num == LLONG_MIN)
    {
        close(fd);
        exit(EXIT_SUCCESS);
    }

    if (lseek(fd, inx * SIZE, SEEK_SET) == -1)
        exit(EXIT_FAILURE);

    min_num = -min_num;

    if (write(fd, &min_num, SIZE) != SIZE)
        exit(EXIT_FAILURE);

    close(fd);

    exit(EXIT_SUCCESS);
}
