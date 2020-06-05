#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>

void task (int sock, int serial, char* key)
{
    int n, nn, max, num;
    char buf[256];
    char str[80];
    pid_t mypid;
    int numplusserial;

    mypid=getpid();
    bzero(buf, 256);
//------------------------------------------ -> KEY SERIAL
    sprintf(buf,"%s\r\n",key);
    nn = strlen(buf);
    n = write(sock,buf,nn);
    if (n < 0)
    {
        sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
        perror(str);
        exit(1);
    }
    sprintf(buf,"%d\r\n",serial);
    nn = strlen(buf);
    n = write(sock,buf,nn);
    if (n < 0)
    {
        sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
        perror(str);
        exit(1);
    }
//------------------------------------------ <- MAX ->
    n = read(sock,buf,255);
    if (n < 0)
    {
        sprintf(str, "%d(%d): ERROR reading MAX", serial, mypid);
        perror(str);
        exit(1);
    }
#if DEBUG
    fprintf(stderr, "%d(%d): buf(MAX)=%s\n", serial, mypid, buf);
#endif
    if (sscanf(buf, "%d", &max) != 1)
    {
        sprintf(str, "%d(%d): Invalid max", serial, mypid);
        perror(str);
        exit(1);
    }
#if DEBUG
    fprintf(stderr, "%d(%d): max=%d\n", serial, mypid, max);
#endif
    sprintf(buf,"%d\r\n",max);
    nn = strlen(buf);
    n = write(sock,buf,nn);
    if (n < 0)
    {
        sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
        perror(str);
        exit(1);
    }
//------------------------------------------ NUM
    for(;;)
    {
        n = read(sock,buf,255);
        if (n < 0)
        {
            sprintf(str, "%d(%d): ERROR reading NUM", serial, mypid);
            perror(str);
            close(sock);
            exit(1);
        }
        if (n == 0)
            break;
#if DEBUG
        fprintf(stderr, "%d(%d): buf(NUM)=%s\n", serial, mypid, buf);
#endif
        if (sscanf(buf, "%d", &num) != 1)
        {
            sprintf(str, "%d(%d): Invalid num", serial, mypid);
            perror(str);
            close(sock);
            exit(1);
        }
#if DEBUG
        fprintf(stderr, "%d(%d): num=%d\n", serial, mypid, num);
#endif
        if (num > max || __builtin_add_overflow(num, serial, &numplusserial))
        {
            sprintf(buf,"%d\r\n",-1);
            nn = strlen(buf);
            n = write(sock,buf,nn);
            if (n < 0)
            {
                sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
                perror(str);
                exit(1);
            }
            close(sock);
            exit(1);
        } else {
            sprintf(buf,"%d\r\n",numplusserial);
            nn = strlen(buf);
            n = write(sock,buf,nn);
            if (n < 0)
            {
                sprintf(str, "%d(%d): ERROR writing to socket", serial, mypid);
                perror(str);
                exit(1);
            }
        }
    }

    close(sock);
    return;
}

void clean_up_child_process(int signal_number)
{
    int status;
    wait(&status);
}

static int newsockfd, sockfd;

void sigINT_TERM(int signal_number)
{
    close(sockfd);
    close(newsockfd);
    kill(getpid(), SIGTERM);
}

void sigTERM(int signal_number)
{
    kill(0, SIGTERM);
    exit(0);
}

int main(int argc, char *argv[])
{
    int port;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    pid_t pid;
    char key[80];
    int serial;
    struct sigaction sigchld_action;

    serial = 0;

    if((argc!=3) || (sscanf(argv[1],"%d",&port) != 1) || (sscanf(argv[2],"%s",key) != 1))
    {
        fprintf(stderr, "%s 5001 KEY\n", argv[0]);
        return 1;
    }
#if DEBUG
    printf("PORT=%d KEY=%s\n", port, key);
#endif
    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchld_action, NULL);
    sigchld_action.sa_handler = &sigINT_TERM;
    sigaction(SIGINT, &sigchld_action, NULL);
    sigchld_action.sa_handler = &sigTERM;
    sigaction(SIGTERM, &sigchld_action, NULL);

    sockfd = socket(AF_INET, SOCK_STREAM , 0);

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

    while (1)
    {
        while ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1 && errno == EINTR)
            continue;
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }

        serial++;
        pid = fork();

        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }

        if (!pid)
        {
            setpgid(getpid(), getpgid(getppid()));
            close(sockfd);
            task(newsockfd, serial, key);
            exit(0);
        }
        else {
            setpgid(getpid(), getpid());
            close(newsockfd);
#if DEBUG
            printf("****\n");
            usleep(999);
#endif
        }
    }
}

// https://it.wikireading.ru/34213
// https://www.opennet.ru/openforum/vsluhforumID1/77819.html
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
