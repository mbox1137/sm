#define DEBUG 0
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

int task (int sock)
{
    int n, nn, num;
    char buf[256];
    char str[80];
    pid_t mypid;

    mypid = getpid();
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
    nn = 4;
    n = read(sock,buf,nn);
//    n = recv(sock,buf,nn, 0);
    if (n != nn)
    {
        sprintf(str, "%d: ERROR reading NUM", mypid);
        perror(str);
        close(sock);
        exit(1);
    }

    if (n == 0)
        return 0;

    num = ntohl(*((int*)buf));
#endif

    close(sock);
    return num;
}

void clean_up_child_process(int signal_number)
{
    int status;
    wait(&status);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, port;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int sum, num;

    if ((argc != 2) || (sscanf(argv[1], "%d", &port) != 1))
    {
        fprintf(stderr, "%s 5001\n", argv[0]);
        return 1;
    }

#if DEBUG
    printf("PORT=%d\n", port);
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

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    sum = 0;

    while (1)
    {
        while ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1 && errno == EINTR)
            continue;
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }

        num=task(newsockfd);

        if (!num)
            break;

        sum += num;
        close(newsockfd);

#if DEBUG
        printf("****\n");
        usleep(999);
#endif

    }

    printf("%d\n", sum);
}

//https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm

