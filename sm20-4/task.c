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

void task (int sock, int serial, char* key) {
   int n, nn, max;
   char buf[256];

   bzero(buf,256);

   sprintf(buf,"%s\r\n",key);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

   sprintf(buf,"%d\r\n",serial);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

   n = read(sock,buf,255);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
#if DEBUG
   fprintf(stderr, "buf=%s\n", buf);
#endif
   if(sscanf(buf, "%d", &max)!=1) {
      perror("Invalid max");
      exit(1);
   }
#if DEBUG
   fprintf(stderr, "max=%d\n", max);
#endif
   sprintf(buf,"%d\r\n",max);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

   return;

   n = read(sock,buf,255);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   printf("Here is the message: %s\n",buf);
   n = write(sock,"I got your message",18);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
	
}
