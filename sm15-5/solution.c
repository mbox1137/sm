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
           char fn[132];
           int line, line1, line2;
           char *cp;
           int k, dk, kl;
           char *nl="\n";
#if DEBUG
           char *delim="----\n";
#endif
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
	k=0;
	kl=-1;
	for(;;) {
            line++;
            if(line>=line2)
                break;
	    while((k<length) && (cp[k]!='\n'))
	        k++;
#if DEBUG
            dk=k-kl-1;
            if(dk>0)
                write(STDOUT_FILENO, &cp[kl+1], dk);
            write(STDOUT_FILENO, nl, 1);
#endif
            kl=k;
            k++;
	    if(k>=length)
	        break;
	}
#if DEBUG
        write(STDOUT_FILENO, delim, 5);
#endif
        if(k<length)
            line--;
	k=kl-1;
	for(;;) {
	    while((k>=0) && (cp[k]!='\n'))
	        k--;
            if(line<=line1-1)
                break;
            line--;
            dk=kl-k-1;
            if(dk>0)
                write(STDOUT_FILENO, &cp[k+1], dk);
            write(STDOUT_FILENO, nl, 1);
            kl=k;
	    if(k<0)
	        break;
            k--;
	}

	munmap(addr, length + offset - pa_offset);
	close(fd);
	exit(EXIT_SUCCESS);
    }
