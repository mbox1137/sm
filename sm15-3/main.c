#define DEBUG 0

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

size_t meml(char *cp, size_t n)
{
    int k, kl = 0;

    for (k = 0; k < n; k++)
        if(cp[k] == '\n')
            kl++;
    if(cp[n-1] != '\n')
        kl++;

    return kl;
}

size_t filel(char *fn)
{
    char *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length;
    size_t k;

    fd = open(fn, O_RDONLY);
    if (fd == -1)
        return -1;

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        return -1;

    if(sb.st_size == 0)
        return 0;

    offset = 0;
    length = sb.st_size;

    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
               /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size)
    {
        fprintf(stderr, "offset is past end of file\n");
        return -1;
    }

    if (offset + length > sb.st_size)
        length = sb.st_size - offset; /* Can't display bytes past end of file */
    else
        length = sb.st_size - offset; /* No length arg ==> display to end of file */

    addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        return -1;

    k = meml(addr, length);

    munmap(addr, length + offset - pa_offset);
    close(fd);
    return k;
}

int main(int argc, char *argv[])
{
    int k;
    char s[132];
    if (argc < 2)
    {
        sprintf(s,"%s *.txt", argv[0]);
        handle_error(s);
    }

    for(k = 1; k < argc; k++)
#if DEBUG
        printf("%d %s\n", filel(argv[k]), argv[k]);
#else
        printf("%d\n", filel(argv[k]));
#endif
    return 0;
}
