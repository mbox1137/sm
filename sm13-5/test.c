#define _GNU_SOURCE
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
 char* path = argv[1];
 int rval;
 /* Проверка существования файла. */
 rval = access(path, F_OK);
 if (rval == 0)
  printf("%s exists\n", path);
 else {
  if (errno == ENOENT)
   printf("%s does not exist\n", path);
  else if (errno == EACCES)
   printf("%s is not accessible\n", path);
  return 0;
 }

 /* Проверка права доступа. */
 rval = access(path, R_OK);
 if (rval == 0)
  printf("%s is readable\n", path);
 else
  printf("%s is not readable (access denied)\n", path);
 /* проверка права записи. */
 rval = access(path, W_OK);
 if (rval == 0)
  printf("%s is writable\n", path);
 else if (errno == EACCES)
  printf("%s is not writable (access denied)\n", path);
 else if (errno == EROFS)
  printf("%s is not writable (read-only filesystem)\n",
   path);
 return 0;
}
