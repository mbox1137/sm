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

       size_t meml(char *cp, size_t n) {
           return(0);
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
               handle_error("open");

           if (fstat(fd, &sb) == -1)           /* To obtain file size */
               handle_error("fstat");

           offset = 0;
           length = sb.st_size;

           pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
               /* offset for mmap() must be page aligned */

           if (offset >= sb.st_size) {
               fprintf(stderr, "offset is past end of file\n");
               exit(EXIT_FAILURE);
           }

           if (offset + length > sb.st_size) {
               length = sb.st_size - offset;
                       /* Can't display bytes past end of file */

           } else {    /* No length arg ==> display to end of file */
               length = sb.st_size - offset;
           }

           addr = mmap(NULL, length + offset - pa_offset, PROT_READ,
                       MAP_PRIVATE, fd, pa_offset);
           if (addr == MAP_FAILED)
               handle_error("mmap");

           k=meml(addr, length);

           munmap(addr, length + offset - pa_offset);
           close(fd);
           return(k);
       }

       int main(int argc, char *argv[])
       {
           int k;
           char s[132];
           if (argc < 2) {
               sprintf(s,"%s *.txt", argv[0]);
               handle_error(s);
           }
           for(k=1; k<argc; k++)
               printf("%d\n", filel(argv[k]));
           exit(EXIT_SUCCESS);
       }
