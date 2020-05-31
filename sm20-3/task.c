#define DEBUG 0

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
   int n, nn, num;
   char buf[256];
   char str[80];
   pid_t mypid;

   mypid=getpid();
   bzero(buf,256);
#if DEBUG
   nn=255;
   n = read(sock,buf,nn);
   if (n == 0) return(0);
   if (n < 0) {
      sprintf(str, "%d: ERROR reading NUM", mypid);
      perror(str);
      close(sock);
      exit(1);
   }
   if(sscanf(buf, "%d", &num)!=1) {
      sprintf(str, "%d: Invalid num", mypid);
      perror(str);
      close(sock);
      exit(1);
   }
   fprintf(stderr, "%d: num=%d\n", mypid, num);
#else
   nn=4;
   n = read(sock,buf,nn);
   if (n != nn) {
      sprintf(str, "%d: ERROR reading NUM", mypid);
      perror(str);
      close(sock);
      exit(1);
   }
   if (n == 0) return(0);
   num=ntohl(*((int*)buf));
#endif
   close(sock);
   return(num);
}
