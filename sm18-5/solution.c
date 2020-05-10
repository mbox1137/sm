#define DEBUG 1
//#define _POSIX_C_SOURCE 200101L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);

    FILE* write_file = fdopen(fd[1], "w");
    FILE* read_file = fdopen(fd[0], "r");
    int x = 0;
    fprintf(write_file, "%d\n", 100);
    fflush(write_file);
    fscanf(read_file, "%d", &x);

    printf("%d\n", x);
}

/*			sm17-5 (mysystem.c)
#define DEBUG 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "mysystem.h"

void addname(CTRLN *z, char *name) {
    int n;
    if(!name) {
        if(z->names)
            free(z->names);
        if(z->pnames)
            free(z->pnames);
        z->kn=0;
        z->nn=0;
        z->kpn=0;
        z->npn=0;
        return;
    }
    n=strlen(name);
    if(n==0) {
        z->kn=0;
        z->kpn=0;
        return;
    }
    if((z->kn+n+1) >= (z->nn)) {
        if(!z->names) {
            z->nn = 1<<13;
            z->names = malloc(z->nn);
            if(z->names == NULL)
                z->names = NULL;
        } else {
            z->nn *= 2;
            z->names = realloc(z->names, z->nn);
            if(z->names == NULL)
                z->names = NULL;
        }
    }
    if((z->kpn) >= (z->npn)) {
        if(!z->pnames) {
            z->npn = 1<<10;
            z->pnames = malloc((z->npn) * sizeof(int));
            if(z->pnames == NULL)
                z->pnames = NULL;
        } else {
            z->npn *= 2;
            z->pnames = realloc(z->pnames, z->npn*sizeof(int));
            if(z->pnames == NULL)
                z->pnames = NULL;
        }
    }
    (z->pnames)[z->kpn]=z->kn;
    strcpy(&((z->names)[z->kn]),name);
    z->kn += n+1;
    z->kpn++;
}

int mysystem(const char *str) {
    char *cmd;
    int status;
    pid_t pid;
    CTRLN ctrln;
    char delim[]=" \f\n\r\t\v";
    char *cp;
    char **args;
    int k;

#if DEBUG
    if(str)
        fprintf(stderr,"str=\"%s\"\n",str);
#endif

    ctrln.names=NULL;
    ctrln.pnames=NULL;
    addname(&ctrln, NULL);	//init
    cp = strtok((char*)str, delim);
    if(!cp)
        return(-1);
    while(cp) {
        addname(&ctrln, cp);
        cp=strtok(NULL, delim);
    }
    args=malloc((ctrln.kpn+1)*sizeof(char*));
    if(args==NULL) {
        return(-2);
    }
    for (k = 0; k < ctrln.kpn; k++)
        args[k]=&ctrln.names[ctrln.pnames[k]];
    args[k]=NULL;
    cmd=args[0];
#if DEBUG
    printf("cmd=\"%s\"\n", cmd);
    for (k = 0; args[k]; k++) {
        printf("argv[%d]=\t\"%s\"\n", k, args[k]);
    }
#endif
    pid = fork();
    if (pid < 0)
    {
        return(1);
    }
    if (!pid)
    {
        execvp(cmd, args);
        exit(1);
    } else {
        free(args);
        addname(&ctrln, NULL);	//finit
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) return(WEXITSTATUS(status));
        else if(WIFSIGNALED(status)) return(1024+WTERMSIG(status));
        else if(WIFSTOPPED(status)) return(1000000+WSTOPSIG(status));
        else if(WIFCONTINUED(status)) return(65535);
        return(0);
    }
}
*/

/*			sm17-1 (prog.c)
#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *cmd;
    int outfd, infd;
    int wstatus;
    pid_t pid;

    if (argc != 4)
    {
        exit(EXIT_FAILURE);
    }

    cmd = argv[1];

    infd = open(argv[2], O_RDONLY);
    if (!infd)
    {
        perror("open infd");
        exit(EXIT_FAILURE);
    }

    outfd = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0666);
    if (!outfd)
    {
        perror("open outfd");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        close(infd);
        close(outfd);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (!pid)
    {
        dup2(infd, 0);
        close(infd);

        dup2(outfd, 1);
        close(outfd);

        execlp(cmd, cmd, NULL);
        exit(EXIT_FAILURE);
    } else
    {
        close(infd);
        close(outfd);
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) exit(WEXITSTATUS(wstatus));
        else exit(EXIT_FAILURE);
    }

    return 0;
}
*/
