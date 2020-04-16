//https://unixhow.com/3169/chto-takoe-i-dlya-chego-nuzhen-sistemnyj-vyzov-mmap
//https://github.com/gcc-mirror/gcc/blob/master/include/leb128.h

#define DEBUG 0
//#define		NNM 15
//#define	NNM (1<<12);		//4K
#define	NNM ((1ll<<32)-1);	//4G-1

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

static inline size_t read_sleb128_to_int64 (unsigned char *buf, unsigned char *buf_end, int64_t *r)
{
    unsigned char *p = buf;
    unsigned int shift = 0;
    int64_t result = 0;
    unsigned char byte;

    for(;;)
    {
        if (p >= buf_end)
            return 0;

        byte = *p++;
        result |= ((u_int64_t) (byte & 0x7f)) << shift;
        shift += 7;
        if ((byte & 0x80) == 0)
            break;
    }
    if (shift < (sizeof (*r) * 8) && (byte & 0x40) != 0)
        result |= -(((u_int64_t) 1) << shift);

    *r = result;

    return p - buf;
}

size_t sum_sLEB128(unsigned char *cp, size_t yn, size_t rn, int64_t *s)
{
    int64_t r;
    size_t dcp, rb, rb0;
    int k;
    k = 0;
    dcp = 0;
    rb0=0;
    *s = 0;
    for(;;)
    {
        rb = read_sleb128_to_int64 (&cp[dcp], &cp[rn], &r);
        if(rb == 0)
            break;
        rb0+=rb;
        dcp += rb;
#if DEBUG
        printf("r=%lld (+%d)\n",r,dcp);
#endif
        *s += r;
        k++;
        if(rb0>yn)
            break;
    }
    return rb0;
}

size_t filel(char *fn, off_t offset, size_t len, off_t *newo, int64_t *r)
{
    char *addr;
    int fd;
    struct stat sb;
    off_t pa_offset;
    size_t rb, ylen;

    fd = open(fn, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
               /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size)
        return(0);

    ylen=len-7;
    if (offset + len > sb.st_size)
    {
        len = sb.st_size - offset;
        ylen=len;
    }
    addr = mmap(NULL, len + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    rb = sum_sLEB128((unsigned char*)(addr+offset-pa_offset), ylen, len, r);

    munmap(addr, len + offset - pa_offset);
    close(fd);
    *newo=offset+rb;
    return rb;
}

int file2(char *fn) {
    off_t start, newstart;
    size_t slen, n;
    int64_t s, sum;
    sum=0;
    start=0;
    slen=NNM;
    for(;;)
    {
        n=filel(fn, start, slen, &newstart, &s);
        if(n==0)
            break;
        sum+=s;
        start=newstart;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    char s[132];

    if (argc < 2)
    {
        sprintf(s,"%s file.bin", argv[0]);
        handle_error(s);
    }

    for(int k = 1; k < argc; k++)
        printf("%d\n", file2(argv[k]));

    return 0;
}
