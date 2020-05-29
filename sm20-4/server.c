#define DEBUG 1

//Unix Socket - Server Examples
//https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

//Antizombie: Асинхронное удаление дочерних процессов
//https://it.wikireading.ru/34213
/*
https://www.opennet.ru/openforum/vsluhforumID1/77819.html
...
Если все процессы вменяемые, то посылка TERM(но не KILL) родителському должна 
привести к схлопыванию всего дерева. Если же по каким-либо причинам корректного 
завершения по TERM не происходит, то после убийства корневого через KILL все 
остальные останутся зомбями и init их сам придушит, а если не придушит, то 
просто грепаем по Zz вывод ps и отдаем KILL всем зомбям. Альтернативно можно 
конечно написать простенький скрипт, который будет проходить по дереву процессов 
начиная от какого-то PID и посылать KILL всем потомкам.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>

#include "server.h"

void clean_up_child_process(int signal_number) {
   int status;
   wait(&status);
}

static int newsockfd, sockfd;

void sigINT_TERM(int signal_number) {
   close(sockfd);
   close(newsockfd);
   kill(getpid(), SIGTERM);
}

int main( int argc, char *argv[] ) {
//   int sockfd, newsockfd, port, clilen;
   int port, clilen;
//   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   pid_t pid;
//   int w;
//   int wstatus;
   char key[80];
   int serial;
//   siginfo_t infop;
 struct sigaction sigchld_action;

   serial=0;

   if(   (argc!=3)
      || (sscanf(argv[1],"%d",&port)!=1)
      || (sscanf(argv[2],"%s",key)!=1)
      )
      {
      fprintf(stderr, "%s 5001 KEY\n", argv[0]);
      return(1);
   }
#if DEBUG
            printf("PORT=%d KEY=%s\n", port, key);
#endif
   memset(&sigchld_action, 0, sizeof(sigchld_action));
   sigchld_action.sa_handler = &clean_up_child_process;
   sigaction(SIGCHLD, &sigchld_action, NULL);
   sigchld_action.sa_handler = &sigINT_TERM;
   sigaction(SIGINT, &sigchld_action, NULL);
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM /*| SOCK_CLOEXEC*/ , 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
      perror("setsockopt(SO_REUSE{ADDR,PORT}) failed");
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
//      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      while ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1 
         && errno == EINTR)
          continue;
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      serial++;
		
      pid = fork();

      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         close(sockfd);
         task(newsockfd, serial, key);
         exit(0);
      }
      else {
         close(newsockfd);
#if DEBUG
            printf("****\n");
            usleep(999);
#endif
      }
		
   } /* end of while */
}
