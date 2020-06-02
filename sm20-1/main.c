#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    char host[1000];
    char service[1000];
    int err, flag = 0;

    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };

    struct addrinfo *result, *inx;
    struct sockaddr_in *ipv4, *min_ipv4 = NULL;

    while (scanf("%s %s", host, service) == 2)
    {
        err = getaddrinfo(host, service, &hints, &result);

        if (err)
        {
            fprintf(stdout, "%s\n", gai_strerror(err));
            continue;
        }

        flag = 0;
        for(inx = result; inx != NULL; inx = inx->ai_next)
        {
            ipv4 = (struct sockaddr_in *)inx->ai_addr;

            if (!flag)
            {
                min_ipv4 = ipv4;
                flag = 1;
                continue;
            }

            if (ntohl(ipv4->sin_addr.s_addr) < ntohl(min_ipv4->sin_addr.s_addr))
                min_ipv4 = ipv4;
        }

        printf("%s:%d\n", inet_ntoa(min_ipv4->sin_addr), ntohs(min_ipv4->sin_port));

        freeaddrinfo(result);
    }

    exit(EXIT_SUCCESS);
}

/*
https://github.com/blackav/hse-caos-2019/tree/master/20-socket
struct addrinfo
{
    int              ai_flags;     // флаги для использования в hints
    int              ai_family;    // для TCP/IP v4 здесь AF_INET, используется в hints
    int              ai_socktype;  // для TCP здесь SOCK_STREAM, используется в hints
    int              ai_protocol;  // уточнение протокола, обычно 0
    socklen_t        ai_addrlen;   // длина адреса для передачи в параметре addrlen в connect или bind
    struct sockaddr *ai_addr;      // адрес для передачи в connect или bind
    char            *ai_canonname;
    struct addrinfo *ai_next;      // указатель на следующий элемент
};
*/
