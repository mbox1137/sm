#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 2
#define MAXUCHAR ((1 << 8) - 1)

int main(int argc, char** argv)
{
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR); //S_IRUSR | S_IWUSR == 0600??
    //int fd = creat(argv[1], S_IRWXU);
    if(fd < 0)
    {
        fprintf (stderr, "Cannot open file '%s'\n", argv[1]);
        return 1;
    }

    unsigned short num;
    unsigned char buf[BUFSIZE];
    size_t count;

    while (scanf("%hu", &num) != EOF)
    {
        buf[1] = num & MAXUCHAR;
        num >>= 8;
        buf[0] = num;

        count = write(fd, buf, BUFSIZE);
        if (count != BUFSIZE)
        {
            fprintf(stderr, "Cannot  write\n");
            return 1;
        }
    }
    if (close (fd) != 0)
    {
        fprintf (stderr, "Cannot close file\n");
        return 1;
    }

    return 0;
}

//https://www.opennet.ru/docs/RUS/zlp/005.html
//http://manpages.ubuntu.com/manpages/precise/ru/man2/open.2.html
//http://dmilvdv.narod.ru/Translate/LDD3/ldd_read_write.html
