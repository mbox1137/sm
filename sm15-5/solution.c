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

       int
       main(int argc, char *argv[])
       {
           char *addr;
           int fd;
           struct stat sb;
           off_t offset, pa_offset;
           size_t length;
           ssize_t s;
           char fn[132];
           int line, line1, line2;
           char *cp, *cpl;
           int ostatok;
           char *fmt;
           int k, kl, ic;
           char *nl="\n";

           if (argc == 1) {
               strcpy(fn,"file.txt");
               line1=4;
               line2=6;
           } else if (argc == 4) {
               if(sscanf(argv[1],"%s",fn)!=1)
                   handle_error("filename");
               if(sscanf(argv[2],"%d",&line1)!=1)
                   handle_error("line1");
               if(sscanf(argv[3],"%d",&line2)!=1)
                   handle_error("line2");
           } else {
               fprintf(stderr, "%s file line1 line2\n", argv[0]);
               exit(EXIT_FAILURE);
           }
#if DEBUG
           printf("%s %d %d\n", fn, line1, line2);
#endif
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

           cp=(char*)addr;
           line=0;
           kl=0;
           for(;;) {
               k=kl;
               while(k<length && cp[k]=='\n') { k++; line++; }
               kl=k;
               while(kl<length && cp[kl]!='\n') kl++;
               if(k==kl) break;
               if(!(line<line2)) break;
//               line++;
           }
           for(;;) {
               while(kl>0 && cp[kl]=='\n') { kl--; line--; }
               if(kl<0) break;
               k=kl;
               if((kl>0) && (kl<length)) kl++;
               while(k>0 && cp[k]!='\n') k--;
               if((k>0) && (k<length)) k++;
               write(STDOUT_FILENO, &cp[k], kl-k); if(cp[k]!='\n') write(STDOUT_FILENO, nl, 1);
               if(line<line1-1) break;
               kl=k-1;
//               line--;
           }

           munmap(addr, length + offset - pa_offset);
           close(fd);
           exit(EXIT_SUCCESS);
       }
