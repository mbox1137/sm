#define DEBUG 0

#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char *names;
    char **pnames;
    off_t kn;
    size_t nn;
    off_t kpn;
    size_t npn;
    } CTRLN;

void addname(CTRLN *z, char *name) {
    size_t n;
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
            z->nn = 1<<10;
            z->names = malloc(z->nn);
        } else {
            z->nn *= 2;
            z->names = realloc(z->names, z->nn);
        }
    }
    if((z->kpn) >= (z->npn)) {
        if(!z->pnames) {
            z->npn = 1<<7;
            z->pnames = malloc(z->npn*sizeof(char*));
        } else {
            z->npn *= 2;
            z->pnames = realloc(z->pnames, z->npn*sizeof(char*));
        }
    }
    (z->pnames)[(z->kpn)++]=&((z->names)[z->kn]);
    strcpy(&((z->names)[z->kn]),name);
    z->kn += n+1;
}

static int mycmp(const void *p1, const void *p2)
{
    return strcasecmp(* (char * const *) p1, * (char * const *) p2);
}

char *lastname(char *path)
{
    char *cp, *lastname, delims[] = "/";
    int n;
    n = strlen(path);
    if ((n>0) && (path[n - 1] == delims[0]))
        path[n - 1] = 0;

    lastname = NULL;
    cp = strtok(path, delims);

    while(cp)
    {
        lastname = cp;
        cp = strtok(NULL, delims);
    }

    return lastname;
}

int filelist(char **names, char *path)
{
    DIR *dir;
    struct dirent *de;
    struct stat statbuf;
    char ffn[PATH_MAX];
    int nf;
    if((dir=opendir(path)) == NULL)
        return 0;
    nf = 0;

    while((de=readdir(dir)) != NULL)
    {
        sprintf(ffn, "%s/%s", path, de->d_name);

        if (stat(ffn, &statbuf) != 0)
            continue;
        if (!S_ISDIR(statbuf.st_mode))
            continue;
        if (strcmp(de->d_name,".") == 0)
            continue;
        if (strcmp(de->d_name,"..") == 0)
            continue;
        if (names)
        {
            names[nf] = calloc(strlen(de->d_name) + 1, sizeof(char));
            if (names[nf] == NULL)
            {
                fprintf(stderr, "calloc error\n");
                exit(1);
            }
            strcpy(names[nf], de->d_name);
        }
        nf++;
    }

    closedir(dir);
    return nf;
}

void traverse_(char *path, char *name)
{
    char** pnames;
    char ffn[PATH_MAX];
    char tmpp[PATH_MAX];
    int k, nf;
    DIR *dir;
    struct stat statbuf;
    if ((dir = opendir(path)) == NULL)
        {
            strerror_r(errno, tmpp, PATH_MAX);
            fprintf(stderr, "Err: opendir (%d=%s) %s\n", errno, tmpp, path);
            return;
        }
    if (lstat(path, &statbuf) != 0)
        {
            fprintf(stderr, "Err: stat (%s)\n", path);
            return;
        }
    closedir(dir);
    if (!S_ISDIR(statbuf.st_mode))
        {
//            fprintf(stderr, "Err: opendir (%s)\n", path);
            return;
        }
#if DEBUG
    printf("%s\n", path);
#else
    strcpy(tmpp, path);
    if (name != NULL)
        printf("cd %s\n", lastname(tmpp));
#endif
    nf=filelist(NULL, path);
    if (nf)
    {
        pnames = calloc(nf, sizeof(char*));
        if (pnames == NULL)
            exit(1);
        filelist(pnames, path);
        qsort(pnames, nf, sizeof(char *), mycmp);

        for (k = 0; k < nf; k++)
        {
            sprintf(ffn, "%s/%s", path, pnames[k]);
        traverse_(ffn,pnames[k]);
        }

        for (k = 0; k < nf; k++)
            if(pnames[k])
                free(pnames[k]);
        if (pnames)
            free(pnames);
    }
#if DEBUG
#else
    if (name != NULL)
        printf("cd ..\n");
#endif
    return;
}

void traverse(char *path, char *name)
{
    CTRLN ctrln;
    ctrln.names=NULL;
    ctrln.pnames=NULL;
    addname(&ctrln, NULL);	//init
    addname(&ctrln, NULL);	//finit
}

int main(int argc, char *argv[])
{
    char *fn = "a";
    if (argc == 2)
        fn=argv[1];
    else if (argc != 1)
    {
        fprintf(stderr, "%s [dir]\n",argv[0]);
        return -1;
    }
    traverse_(fn, NULL);
    return 0;
}
