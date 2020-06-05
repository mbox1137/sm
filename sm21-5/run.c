#include <string.h>
#include <sys/wait.h>

#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include "run.h"

static int retval;

void clean_up_child_process(int signal_number)
{
    int status;
    retval=0;
    wait(&status);
         if (WIFEXITED(status))    retval = (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))  retval = (1024+WTERMSIG(status));
    else if (WIFSTOPPED(status))   retval = (1024+WSTOPSIG(status));
    else if (WIFCONTINUED(status)) retval = (1024+SIGCONT);
    return;
}

int run(const char* cmd, 
        const char* input, 
        char** poutput, 
        char** perror, 
        int timeot) {

    struct sigaction sigchld_action;
    retval=0;
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);
    return(retval);
}
