#define DEBUG 1

//Unix Socket - Server Examples
//https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

#include "server.h"

int task (int sock) {
   int n, num;
   char buf[256];
   char str[80];
   pid_t mypid;

   mypid=getpid();
   bzero(buf,256);
   n = read(sock,buf,255);
   if (n < 0) {
      sprintf(str, "%d: ERROR reading NUM", mypid);
      perror(str);
      close(sock);
      exit(1);
   }
   if (n == 0) return(0);
#if DEBUG
   fprintf(stderr, "%d: buf(NUM)=%s\n", mypid, buf);
#endif
   if(sscanf(buf, "%d", &num)!=1) {
      sprintf(str, "%d: Invalid num", mypid);
      perror(str);
      close(sock);
      exit(1);
   }
#if DEBUG
   fprintf(stderr, "%d: num=%d\n", mypid, num);
#endif
   close(sock);
   return(num);
}
