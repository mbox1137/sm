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
    char delim[]=" \t";
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
    while(cp) {
        addname(&ctrln, cp);
        cp=strtok(NULL, delim);
    }
    args=malloc((ctrln.kpn+1)*sizeof(char*));
    if(args==NULL) {
        exit(-2);
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
        exit(EXIT_FAILURE);
    } else {
        free(args);
        addname(&ctrln, NULL);	//finit
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) exit(WEXITSTATUS(status));
        else exit(EXIT_FAILURE);
    }
    return(0);
}

/*
#define DEBUG 0

int main(int argc, char *argv[])
{
    int outfd, infd;

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


    return 0;
}
*/
