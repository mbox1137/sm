#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>

#include "server.h"

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, port;
   socklen_t clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int sum, num;
   char host[132];

   if(   (argc!=4)
      || (sscanf(argv[1],"%s",host)!=1)
      || (sscanf(argv[2],"%d",&port)!=1)
      || (sscanf(argv[3],"%d",&num)!=1)
      )
      {
      fprintf(stderr, "%s localhost 5001 123\n", argv[0]);
      return(1);
   }
#if DEBUG
            printf("%s:%d\n", host, port);
#endif
   return(0);

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
      perror("setsockopt(SO_REUSE{ADDR,PORT}) failed");
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port);
   
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   sum=0;

   while (1) {
      while ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1 
         && errno == EINTR)
          continue;
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
//      close(sockfd);
      num=task(newsockfd);
      if(!num) break;
      sum+=num;
      close(newsockfd);
#if DEBUG
      printf("****\n");
      usleep(999);
#endif
   } /* end of while */
   printf("%d\n", sum);
}
