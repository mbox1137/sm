#define DEBUG 1
#define _GNU_SOURCE 1

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
    off_t *pnames;
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
            z->nn = 1<<12;
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
            z->npn = 1<<9;
            z->pnames = malloc(z->npn*sizeof(off_t));
            if(z->pnames == NULL)
                z->pnames = NULL;
        } else {
            z->npn *= 2;
            z->pnames = realloc(z->pnames, z->npn*sizeof(off_t));
            if(z->pnames == NULL)
                z->pnames = NULL;
        }
    }
    (z->pnames)[z->kpn]=z->kn;
    strcpy(&((z->names)[z->kn]),name);
    z->kn += n+1;
    z->kpn++;
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

static int mycmp_(const void *p1, const void *p2)
{
    return strcasecmp(* (char * const *) p1, * (char * const *) p2);
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
        qsort(pnames, nf, sizeof(char *), mycmp_);

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

static int mycmp(off_t *k1, off_t *k2, void *pz)
{
    char *p1, *p2;
    CTRLN *z;
    z=(CTRLN*) pz;
    p1=&(z->names[z->pnames[*k1]]);
    p2=&(z->names[z->pnames[*k2]]);
    return strcasecmp(p1, p2);
}

void traverse(char *path, char *name)
{
    CTRLN ctrln;
    ctrln.names=NULL;
    ctrln.pnames=NULL;
    struct stat statbuf;
    char ffn[PATH_MAX];
    char tmpp[PATH_MAX];
    off_t k;
    DIR *dir;
    struct dirent *de;

    addname(&ctrln, NULL);	//init

    strcpy(tmpp, path);
#if DEBUG
    printf("cd %s\n", tmpp);
#else
    if (name)
        printf("cd %s\n", lastname(tmpp));
#endif
    if ((dir = opendir(path)) == NULL)
        {
            strerror_r(errno, tmpp, PATH_MAX);
            fprintf(stderr, "Err: opendir (%d=%s) %s\n", errno, tmpp, path);
            return;
        }
    while((de=readdir(dir)) != NULL)
    {
        sprintf(ffn, "%s/%s", path, de->d_name);

        if (lstat(ffn, &statbuf) != 0)
            continue;
        if (!S_ISDIR(statbuf.st_mode))
            continue;
        if (strcmp(de->d_name,".") == 0)
            continue;
        if (strcmp(de->d_name,"..") == 0)
            continue;
        addname(&ctrln, de->d_name);
    }
    closedir(dir);
//    qsort_r(ctrln.pnames, ctrln.npn, sizeof(off_t), mycmp, &ctrln);

    for (k = 0; k < ctrln.kpn; k++)
    {
        sprintf(ffn, "%s/%s", path, &ctrln.names[ctrln.pnames[k]]);
        traverse(ffn, &ctrln.names[ctrln.pnames[k]]);
    }
    addname(&ctrln, NULL);	//finit
#if DEBUG
#else
    if(name)
        printf("cd ..\n");
#endif
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
    traverse(fn, NULL);
    return 0;
}
