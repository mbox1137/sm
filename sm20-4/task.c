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
   int n, nn, max, num;
   char buf[256];
   char str[80];
   pid_t mypid;
   int numplusserial;

   mypid=getpid();
   bzero(buf,256);
//------------------------------------------ -> KEY SERIAL
   sprintf(buf,"%s\r\n",key);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
      perror(str);
      exit(1);
   }
   sprintf(buf,"%d\r\n",serial);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
      perror(str);
      exit(1);
   }
//------------------------------------------ <- MAX ->
   n = read(sock,buf,255);
   if (n < 0) {
      sprintf(str, "%d(%d): ERROR reading MAX", serial, mypid);
      perror(str);
      exit(1);
   }
#if DEBUG
   fprintf(stderr, "%d(%d): buf(MAX)=%s\n", serial, mypid, buf);
#endif
   if(sscanf(buf, "%d", &max)!=1) {
      sprintf(str, "%d(%d): Invalid max", serial, mypid);
      perror(str);
      exit(1);
   }
#if DEBUG
   fprintf(stderr, "%d(%d): max=%d\n", serial, mypid, max);
#endif
   sprintf(buf,"%d\r\n",max);
   nn=strlen(buf);
   n = write(sock,buf,nn);
   if (n < 0) {
      sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
      perror(str);
      exit(1);
   }
//------------------------------------------ NUM
   for(;;) {
      n = read(sock,buf,255);
      if (n < 0) {
         sprintf(str, "%d(%d): ERROR reading NUM", serial, mypid);
         perror(str);
         close(sock);
         exit(1);
      }
      if (n == 0) {
         break;
      }
#if DEBUG
      fprintf(stderr, "%d(%d): buf(NUM)=%s\n", serial, mypid, buf);
#endif
      if(sscanf(buf, "%d", &num)!=1) {
         sprintf(str, "%d(%d): Invalid num", serial, mypid);
         perror(str);
         close(sock);
         exit(1);
      }
#if DEBUG
      fprintf(stderr, "%d(%d): num=%d\n", serial, mypid, num);
#endif
      if(num > max || __builtin_add_overflow(num, serial, &numplusserial)) {
         sprintf(buf,"%d\r\n",-1);
         nn=strlen(buf);
         n = write(sock,buf,nn);
         if (n < 0) {
            sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
            perror(str);
            exit(1);
         }
         close(sock);
         exit(1);
      } else {
         sprintf(buf,"%d\r\n",numplusserial);
         nn=strlen(buf);
         n = write(sock,buf,nn);
         if (n < 0) {
            sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
            perror(str);
            exit(1);
         }
      }
   }
   close(sock);
   return;
}
