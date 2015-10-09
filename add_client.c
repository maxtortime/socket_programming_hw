#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

    int client_len;
    int client_sockfd;

    FILE *fp_in;
    char buf_in[255];
    char buf_get[255];

    struct sockaddr_in clientaddr;

    if (argc != 2)
    {
        printf("Usage : ./add_client [port]\n");
        printf("Example    : ./add_client 4444\n");
        exit(0);
    }


    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(atoi(argv[1]));

    client_len = sizeof(clientaddr);

    if (connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0)
    {
        perror("Connect error: ");
        exit(0);
    }
    while(1)
    {
        printf(">: ");
        fgets(buf_in, 255,stdin);

        buf_in[strlen(buf_in) - 1] = '0';
        write(client_sockfd, buf_in, 255);
        if (strncmp(buf_in, "quit", 4) == 0)
        {
            close(client_sockfd);
            exit(0);
        }
        while(1)
        {
            read(client_sockfd, buf_get, 255);
            if (strncmp(buf_get, "end", 3) == 0)
                break;

            printf("%s", buf_get);
        }
    }

    close(client_sockfd);
    exit(0);
}
