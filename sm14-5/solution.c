//https://developer.ibm.com/technologies/linux/tutorials/l-dynamic-libraries/
//https://ru.stackoverflow.com/questions/538296/%D0%9A%D0%B0%D0%BA-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0%D1%8E%D1%82-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D1%81-%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D1%8B%D0%BC-%D1%87%D0%B8%D1%81%D0%BB%D0%BE%D0%BC-%D0%B0%D1%80%D0%B3%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2-%D0%B2-c

/*
void func(char *, char *, int, double);
./solution libc.so.6 printf vssid 'Hello: %s, %d, %f' abc 10 12.4
Hello: abc, 10, 12.400000
*/

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <math.h>

#define LIB 1
#define FUNC 2
#define SIGN 3

static int cfk;

struct cf {
  unsigned char c[64];
  };

void cfd(struct cf *s, double x) {
  *((double*)&(s->c[cfk])) = x;
  cfk+=sizeof(double);
  return;
}

void cfi(struct cf *s, int i) {
  *((int*)&(s->c[cfk])) = i;
  cfk+=sizeof(int);
  return;
}

int main( int argc, char *argv[] )
{
  struct cf frame;
  int k,n;
  int i;
  double d;
  char *s;
  void *dl_handle;
  void (*func)(void);
  char *error;

  n=strlen(argv[SIGN]);
  if(argc<=SIGN || argc!=SIGN+n) {
    fprintf(stderr,"./solution libc.so.6 printf vssid 'Hello: %%s, %%d, %%f' abc 10 12.4\n");
    return(-1);
  }
  for(k=1; k<n; k++) {
//    printf("%c: %s\n", argv[SIGN][k], argv[SIGN+k]);
    switch(argv[SIGN][k]) {
    case 'i':
      sscanf(argv[SIGN+k],"%d",&i);
      cfi(&frame,i);
      break;
    case 'd':
      sscanf(argv[SIGN+k],"%lf",&d);
      cfd(&frame,d);
      break;
    case 's': 
      i=(int)argv[SIGN+k];
      cfi(&frame,i);
      break;
    }
  }
//  printf("cfk=%d\n",cfk);

  dl_handle = dlopen(argv[LIB],RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "!!! %s\n", dlerror() );
    return(-1);
  }

  func = dlsym(dl_handle,argv[FUNC]);
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr,"!!! %s\n", error );
    return(-1);
  }

  typedef void ((*fcfv)(struct cf));
  typedef int ((*fcfi)(struct cf));
  typedef double ((*fcfd)(struct cf));
  typedef char* ((*fcfs)(struct cf));
  switch(argv[SIGN][0]) {
  case 'v': 
    (*((fcfv)func))(frame);
    printf("\n");
    break;
  case 'i':
    i=(*((fcfi)func))(frame);
    printf("%d\n",i);
    break;
  case 'd':
    d=(*((fcfd)func))(frame);
    printf("%.10g\n",d);
    break;
  case 's': 
    s=(char*)(*((fcfs)func))(frame);
    printf("%s\n",s);
    break;
  }

  dlclose( dl_handle );
  return(0);
}

