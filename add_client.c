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
    const int BUF_SIZE = 255, GREETING_SIZE = 50, NAME_SIZE = 20;

    int client_len;
    int client_sockfd;

    char buf_in[BUF_SIZE];
    char buf_get[BUF_SIZE];
    char name[NAME_SIZE];
    char greeting[GREETING_SIZE];

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
    
     // Greeting
     printf("Please input your name. (length:~20)> ");
     fgets(name, NAME_SIZE, stdin);

     /* Remove trailing newline, . */
     if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
        name[strlen (name) - 1] = '\0';

     //sprintf(greeting,"Hello This is %s",name);

     //write(client_sockfd, greeting, GREETING_SIZE);
     //read(client_sockfd, buf_get, BUF_SIZE);
     //printf("%s\n", buf_get);
    

    while(1)
    {
        memset(buf_get, '\0', BUF_SIZE);
        memset(buf_in, '\0', BUF_SIZE);

        printf("%s> ",name);
        fgets(buf_in, BUF_SIZE, stdin);

        /* Remove trailing newline, if there. */
        if ((strlen(buf_in)>0) && (buf_in[strlen (buf_in) - 1] == '\n'))
            buf_in[strlen (buf_in) - 1] = '\0';

        write(client_sockfd, buf_in, BUF_SIZE);
        read(client_sockfd, buf_get, BUF_SIZE);

        // When client inputs quit.
        if (strncmp(buf_in, "quit", 4) == 0)
        {
            printf("%s\n", buf_get);
            close(client_sockfd);
            exit(0);
        }
       
        printf("server-> %s\n", buf_get);
    }

    close(client_sockfd);
    exit(0);
}
