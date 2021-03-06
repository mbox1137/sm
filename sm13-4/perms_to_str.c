//http://isaleksey.blogspot.com/2011/04/
#include <stdio.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>
#include "perms_to_str.h"

const char *perms_to_str(char *buf, size_t size, int perms)
{
    int k;
    char tperms[10];
    char tpnames[]="rwx";
    mode_t mode;
    tperms[9]=0;
    mode=1<<8;
    k=0;
    while(mode) {
        tperms[k]=perms&mode?tpnames[k%3]:'-';
        k++;
        mode>>=1;
    }
/*
    mode=S_ISUID | S_ISGID | S_ISVTX;
    mode|=S_IRUSR|S_IWUSR|S_IXUSR;
    mode|=S_IRGRP|S_IWGRP|S_IXGRP;
    mode|=S_IROTH|S_IWOTH|S_IXOTH;
    sprintf(buf, "0%o", perms);
*/
    if(perms & S_ISUID)
        if(perms & (S_IXGRP|S_IXOTH))
            tperms[2]='s';
    if(perms & S_ISGID)
        if(perms & S_IXOTH)
            tperms[5]='s';
    if(perms&S_ISVTX)
        if((perms & S_IWOTH) && (perms & S_IXOTH))
            tperms[8]='t';

    for(k=0; k<size; k++) {
        if(k>=size-1)
            break;
        buf[k]=tperms[k];
        if(tperms[k]==0)
            break;
    }
    buf[k]=0;
    return(buf);
}
