//(17-1) + (17-5) + ...

/*			sm17-5 (solution.c)	*/
#define DEBUG 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "addname.h"
#include "solution.h"

int solution(const char *str) {
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
