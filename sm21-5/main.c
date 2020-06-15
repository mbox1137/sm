#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "run.h"

int main(int argc, char** argv) {
    char *cmd;
    char *inp;
    char* out;
    char* err;
    int rv;
    int tout;
    char tmp[132];

    if(argc==4)
    {
        cmd=argv[1];
        inp=argv[2];
        sscanf(argv[3], "%d", &tout);
    } else {
        fprintf(stderr, "%s bc \"2+2*2\" 10\n", argv[0]);
        return(1);
    }
    strcpy(tmp, inp);
//    strcat(tmp, "\n");
    printf("cmd=%s\n",cmd);
    printf("inp=%s\n",inp);
    printf("tout=%d\n", tout);
    rv=run(cmd, tmp, &out, &err, tout);
    printf("rv=%d(%02X:%02X)\n",rv,rv/256,rv%256);
    printf("out=%s\n",out);
    printf("err=%s\n",err);
    free(out);
    free(err);
    return(rv);
}
