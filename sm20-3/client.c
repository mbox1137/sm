#define DEBUG 1
#define ASCII 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>

//#include "server.h"

static int task (int sfd, int argc, char** argv)
{
    int nn, num, j, len;
    char buf[256];

    bzero(buf,256);

#if ASCII
    nn = 255;
    n = read(sock,buf,nn);
    if (n == 0)
        return 0;

    if (n < 0)
    {
        sprintf(str, "%d: ERROR reading NUM", mypid);
        perror(str);
        close(sock);
        exit(1);
    }

    if (sscanf(buf, "%d", &num) != 1)
    {
        sprintf(str, "%d: Invalid num", mypid);
        perror(str);
        close(sock);
        exit(1);
    }
    fprintf(stderr, "%d: num=%d\n", mypid, num);
#else
           for (j = 3; j < argc; j++) {
               printf("argv[%d] = %s\n", j, argv[j]);
               sscanf(argv[j], "%d", &num);
               num = htonl(num);
               printf("num = %d\n", ntohl(num));
               len = 4;
               nn=write(sfd, &num, len);
//               nn=send(sfd, (const void *)(&num), len, 0);
               fprintf(stderr, "len=%d nn=%d\n",len,nn);
               if (nn != len) {
                   perror("write");
                   exit(EXIT_FAILURE);
               }
//               fsync(sfd);
           }
           exit(EXIT_SUCCESS);
#endif
    close(sfd);
    return(0);
}

int main(int argc, char *argv[])
{
    int sockfd, fd, port;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int sum, num;
    char host[132];

    if ((argc > 2)
        || (sscanf(argv[1], "%s", host) != 1)
        || (sscanf(argv[2], "%d", &port) != 1)
        )
    {
        fprintf(stderr, "%s 5001\n", argv[0]);
        return 1;
    }

#if DEBUG
    printf("%s:%d\n", host, port);
#endif

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
      perror("setsockopt(SO_REUSE{ADDR,PORT}) failed");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    clilen = sizeof(cli_addr);
    sum = 0;

    for(;;)
    {
        fd=connect(sockfd, (struct sockaddr *) &cli_addr, clilen);
        if (fd < 0)
        {
            perror("ERROR on connect");
            exit(1);
        }
#if DEBUG
        printf("task\n");
#endif
        num = task(sockfd, argc, argv);
        if (!num)
            break;
        sum += num;
        close(sockfd);
#if DEBUG
        printf("****\n");
#endif
    }
    printf("%d\n", sum);
}

//https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

