#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

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
                exit(1);
            strcpy(names[nf], de->d_name);
        }
        nf++;
    }

    closedir(dir);
    return nf;
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
    if (path[n - 1] == delims[0])
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

void traverse(char *path, char *name)
{
    char** pnames;
    char ffn[PATH_MAX];
    char tmpp[PATH_MAX];
    int k, nf;
    DIR *dir;
    struct stat statbuf;
    if ((dir = opendir(path)) == NULL)
        return;
#if 1
    if (stat(path, &statbuf) != 0)
        return;
    if (!S_ISDIR(statbuf.st_mode))
        return;
    strcpy(tmpp, path);
    if (name != NULL)
        printf("cd %s\n", lastname(tmpp));
#else
    if (name)
        printf("cd %s\n", name);
    else
        printf("cd %s\n", path);
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
            traverse(ffn,pnames[k]);
        }

        for (k = 0; k < nf; k++)
            if(pnames[k])
                free(pnames[k]);
        if (pnames)
            free(pnames);
    }
    if (name != NULL)
        printf("cd ..\n");

    return;
}


int main(int argc, char *argv[])
{
    char *fn = "a";
    if (argc == 2)
        fn=argv[1];
    else if (argc != 1)
    {
        fprintf(stderr, "main [a]\n");
        return -1;
    }

    traverse(fn, NULL);

    return 0;
}
