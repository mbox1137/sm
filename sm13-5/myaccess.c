#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "myaccess.h"

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    int k, rwx;
/*
        task->uid=77;
        task->gid_count=3;
        int tmp[]={77,88,99};
        task->gids=tmp;
//
        stb->st_uid=0;
        stb->st_gid=88;
        stb->st_mode=0660;
//
        access=6;
*/
    if(task->uid==0)
        return(1);
    rwx=0;
    if(task->uid==stb->st_uid)
        rwx=(stb->st_mode>>6)&7;
    else
    {
        for(k=0; k<task->gid_count; k++)
            if(task->gids[k]==stb->st_gid)
                break;
        if(k<task->gid_count)
            rwx=(stb->st_mode>>3)&7;
        else
            rwx=stb->st_mode&7;
    }
    if(access == (rwx & access))
        return(1);
    else
        return(0);
}
