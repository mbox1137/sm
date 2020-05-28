#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <memory.h>
#include <inttypes.h>
#include <math.h>

#define OFFSET 0
#define DEBUG 0

int main(int argc, char *argv[])
{
    if (argc != 4)
        exit(EXIT_FAILURE);

    int rows, cols, k;
    if (sscanf(argv[2], "%d", &rows) != 1)
        exit(EXIT_FAILURE);
    if (sscanf(argv[3], "%d", &cols) != 1)
        exit(EXIT_FAILURE);

    long long mat_size = rows * cols * sizeof(double);

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);

    if (fd < 0)
        exit(EXIT_FAILURE);

    if (ftruncate(fd, mat_size) == -1)
    {
        close(fd);
        exit(EXIT_FAILURE);
    }

    double *data = mmap(NULL, mat_size, PROT_WRITE, MAP_SHARED, fd, OFFSET);

    if (data == MAP_FAILED)
    {
        close(fd);
        exit(EXIT_FAILURE);
    }

    for(double i = 0; i < rows; ++i)
    {
        for(double j = 0; j < cols; ++j)
        {
            k = cols * i + j;
            data[k] = 2*sin(i) + 4*cos(j/2);
        }
    }

#if DEBUG
    int i;
    for (i = 0; i < rows * cols; ++i)
        printf("%lf\n", data[i]);
#endif

    if (munmap(data, mat_size) == -1)
        exit(EXIT_FAILURE);

    close(fd);

    exit(EXIT_SUCCESS);
}
