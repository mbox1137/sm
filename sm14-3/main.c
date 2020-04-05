//https://developer.ibm.com/technologies/linux/tutorials/l-dynamic-libraries/

#define DEBUG 1

#include <stdio.h>
#include <malloc.h>
#include <string.h>
//#include <sys/types.h>
#include <dirent.h>
//#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

int filelist(char **names, char *path) {
  DIR *dir;
  struct dirent *de;
  struct stat statbuf;
  char ffn[PATH_MAX];
  int nf;
  if((dir=opendir(path))==NULL) return(0);
  nf=0;
  while((de=readdir(dir))!=NULL) {
    sprintf(ffn, "%s/%s", path, de->d_name);
    if(access(ffn, R_OK|X_OK|F_OK)) continue;
    if(stat(ffn, &statbuf)!=0) continue;
    if(!S_ISDIR(statbuf.st_mode)) continue;
    if(strcmp(de->d_name,".")==0) continue;
    if(strcmp(de->d_name,"..")==0) continue;
    if(names) {
      names[nf]=calloc(strlen(de->d_name)+1,sizeof(char));
      strcpy(names[nf], de->d_name);
    }
    nf++;
  }
  closedir(dir);
  return(nf);
}

static int mycmp(const void *p1, const void *p2) {
  return strcasecmp(* (char * const *) p1, * (char * const *) p2);
}

void traverse(char *path, char *name) {
  char** pnames;
  char ffn[PATH_MAX];
  int k, nf;
  DIR *dir;
  if((dir=opendir(path))==NULL) return;
  if(name)
    printf("cd %s\n",name);
  else
    printf("cd %s\n",path);
  nf=filelist(NULL, path);
  if(nf) {
    pnames=calloc(nf, sizeof(char*));
    filelist(pnames, path);
    qsort(pnames, nf, sizeof(char *), mycmp);
    for(k=0; k<nf; k++) {
      sprintf(ffn, "%s/%s", path, pnames[k]);
      traverse(ffn,pnames[k]);
    }
    for(k=0; k<nf; k++)
      if(pnames[k])
        free(pnames[k]);
    if(pnames)
      free(pnames);
  }
  printf("cd ..\n");
  return;
}

int main( int argc, char *argv[] )
{
  char *fn="a";
  int nf;
  if(argc==2) fn=argv[1];
  else if(argc!=1) {
    fprintf(stderr,"main [a]\n");
    return(-1);
  }
  traverse(fn, NULL);
}
