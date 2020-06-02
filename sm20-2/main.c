#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
        exit(EXIT_FAILURE);

    struct addrinfo hints = { .ai_family = PF_INET, .ai_socktype = SOCK_STREAM};
    struct addrinfo *result;
    int sockfd, sockfd2, serv_k, success, i;
    unsigned long long ans;
    FILE *in, *out;

    if (getaddrinfo(argv[1], argv[2], &hints, &result) < 0)
        exit(EXIT_SUCCESS);

    sockfd = socket(result->ai_family, result->ai_socktype, 0);

    if (sockfd < 0)
    {
        freeaddrinfo(result);
        exit(EXIT_SUCCESS);
    }

    if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0)
    {
        freeaddrinfo(result);
        exit(EXIT_SUCCESS);
    }

    sockfd2 = dup(sockfd);

    if (sockfd2 == -1)
        exit(EXIT_FAILURE);

    in = fdopen(sockfd, "r");

    if (in == NULL)
        exit(EXIT_FAILURE);

    out = fdopen(sockfd2, "w");

    if (out == NULL)
        exit(EXIT_FAILURE);

    success = fprintf(out, "%s\n", argv[3]);

    fflush(out);

    if (success < 0)
    {
        fclose(in);
        fclose(out);
        freeaddrinfo(result);
        exit(EXIT_SUCCESS);
    }

    if (fscanf(in, "%d", &serv_k) < 0)
    {
        fclose(in);
        fclose(out);
        freeaddrinfo(result);
        exit(EXIT_SUCCESS);
    }

    for(i = 0; i <= serv_k; ++i)
    {
        success = fprintf(out, "%d\n", i);

        fflush(out);

        if (success < 0)
        {
            fclose(in);
            fclose(out);
            freeaddrinfo(result);
            exit(EXIT_SUCCESS);
        }
    }

    if (fscanf(in, "%llu", &ans) < 0)
    {
        fclose(in);
        fclose(out);
        freeaddrinfo(result);
        exit(EXIT_SUCCESS);
    }

    printf("%llu\n", ans);
    fflush(stdout);

    fclose(in);
    fclose(out);

    freeaddrinfo(result);

    exit(EXIT_SUCCESS);
}
