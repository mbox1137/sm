//https://developer.ibm.com/technologies/linux/tutorials/l-dynamic-libraries/

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <math.h>

#define MAX_STRING      80

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
