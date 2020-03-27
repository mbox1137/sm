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

void traverse(char *path) {
  char** pnames;
  char ffn[PATH_MAX];
//  printf("%s\n", path);
  int k, nf;
  nf=filelist(NULL, path);
  if(nf==0) return;
  pnames=calloc(nf, sizeof(char*));
  filelist(pnames, path);
  qsort(pnames, nf, sizeof(char *), mycmp);
  for(k=0; k<nf; k++) {
    sprintf(ffn, "%s/%s", path, pnames[k]);
    printf("cd %s",pnames[k]);
#if DEBUG
    printf("\t-> %s",ffn);
#endif
    printf("\n");
    traverse(ffn);
    printf("cd ..");
#if DEBUG
    printf("\t-> %s",path);
#endif
    printf("\n");
  }
  for(k=0; k<nf; k++) {
   if(pnames[k]) free(pnames[k]);
  }
  if(pnames) free(pnames);
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
  traverse(fn);
}

//man 7 inode
/*
           struct stat {
               dev_t     st_dev;         // ID of device containing file 
               ino_t     st_ino;         // Inode number 
               mode_t    st_mode;        // File type and mode 
               nlink_t   st_nlink;       // Number of hard links 
               uid_t     st_uid;         // User ID of owner 
               gid_t     st_gid;         // Group ID of owner 
               dev_t     st_rdev;        // Device ID (if special file) 
               off_t     st_size;        // Total size, in bytes 
               blksize_t st_blksize;     // Block size for filesystem I/O 
               blkcnt_t  st_blocks;      // Number of 512B blocks allocated 

               // Since Linux 2.6, the kernel supports nanosecond
               // precision for the following timestamp fields.
               // For the details before Linux 2.6, see NOTES. 

               struct timespec st_atim;  // Time of last access 
               struct timespec st_mtim;  // Time of last modification 
               struct timespec st_ctim;  // Time of last status change 

           #define st_atime st_atim.tv_sec      // Backward compatibility 
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };
*/
