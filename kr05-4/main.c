#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define SIZE sizeof(unsigned)
#define BYTE 8
#define MAX 0xFF

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(EXIT_FAILURE);

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0600);

    if (fd == -1)
        exit(EXIT_FAILURE);

    unsigned num, temp_num = 0;

    while(scanf("%u", &num) == 1)
    {
        for(int i = 0; i < SIZE; ++i)
        {
            temp_num = (temp_num << BYTE) | (num & MAX);
            num >>= BYTE;
        }

        if (write(fd, &temp_num, SIZE) != SIZE)
            exit(EXIT_FAILURE);
    }

    close(fd);

    exit(EXIT_SUCCESS);
}
