//https://developer.ibm.com/technologies/linux/tutorials/l-dynamic-libraries/
//https://ru.stackoverflow.com/questions/538296/%D0%9A%D0%B0%D0%BA-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0%D1%8E%D1%82-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D1%81-%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D1%8B%D0%BC-%D1%87%D0%B8%D1%81%D0%BB%D0%BE%D0%BC-%D0%B0%D1%80%D0%B3%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2-%D0%B2-c

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <math.h>

#define MAX_STRING      80

static int cfp;

struct cf {
  unsigned char c[64];
  };

double dsol(struct cf x);

double dsol(struct cf x){
  return(NAN);
}

void appd(struct cf *s, double x) {
  *((double*)&(s->c[cfp])) = x;
  cfp+=sizeof(double);
  return;
}

void appi(struct cf *s, int i) {
  *((int*)&(s->c[cfp])) = i;
  cfp+=sizeof(int);
  return;
}

double invoke_method( char *lib, char *method, double argument )
{
  void *dl_handle;
  double (*func)(double);
  double res;
  char *error;

  /* Open the shared object */
  dl_handle = dlopen( lib, RTLD_LAZY );
  if (!dl_handle) {
    printf( "!!! %s\n", dlerror() );
    return(NAN);
  }

  /* Resolve the symbol (method) from the object */
  func = dlsym( dl_handle, method );
  error = dlerror();
  if (error != NULL) {
    printf( "!!! %s\n", error );
    return(NAN);
  }

  /* Call the resolved method and print the result */
  res=(*func)(argument);

  /* Close the object */
  dlclose( dl_handle );

  return(res);
}

int main( int argc, char *argv[] )
{
  char line[MAX_STRING+1];
  char lib[MAX_STRING+1];
  char method[MAX_STRING+1];
  double argument;

  struct cf x;
  argument=dsol(x);
  cfp=0;
  appd(&x, argument);
  appd(&x, 123);
  return(0);

  strcpy(lib,"libm.so");
  if(argc!=2) {
    fprintf(stderr,"./main sin\n");
    return(-1);
  }
  strcpy(method,argv[1]);

  while (1) {
    if(scanf("%lf", &argument)!=1)
      break;
    printf("%.10g\n", invoke_method(lib,method,argument) );
  }
}
