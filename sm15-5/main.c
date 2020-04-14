//https://stackoverflow.com/questions/6565357/git-push-requires-username-and-password
//git config credential.helper store
//git config --global credential.helper 'cache --timeout 7200'

#define DEBUG 0

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 132

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	char fn[N];
	unsigned char buf[N];
	int h,n;
	int line1, line2;

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
	h=open(fn, O_RDONLY);
	n=read(h,buf,N);
	write(STDOUT_FILENO, buf, n);
	close(h);
}
