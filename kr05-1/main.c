#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define SIZE sizeof(int)

int main(int argc, char** argv)
{
    if (argc != 2)
        exit(EXIT_FAILURE);

    char buf1[SIZE];
    char buf2[SIZE];

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
        exit(EXIT_FAILURE);

    struct stat file;

    if (stat(argv[1], &file) == -1)
        exit(EXIT_FAILURE);

    if (file.st_size < 2 * SIZE)
        exit(EXIT_FAILURE);

    if (read(fd, buf1, SIZE) != SIZE)
        exit(EXIT_FAILURE);

    if (lseek(fd, file.st_size - SIZE, SEEK_SET) == -1)
        exit(EXIT_FAILURE);

    if (read(fd, buf2, SIZE) != SIZE)
        exit(EXIT_FAILURE);

    if (lseek(fd, file.st_size - SIZE, SEEK_SET) == -1)
        exit(EXIT_FAILURE);

    if (write(fd, buf1, SIZE) != SIZE)
        exit(EXIT_FAILURE);

    if (lseek(fd, 0, SEEK_SET) == -1)
        exit(EXIT_FAILURE);

    if (write(fd, buf2, SIZE) != SIZE)
        exit(EXIT_FAILURE);

    close(fd);

    exit(EXIT_SUCCESS);
}


