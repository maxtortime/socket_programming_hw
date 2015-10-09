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
    int server_sockfd, client_sockfd;
    int state, client_len;
    int pid;
    int greeted = 0;

    struct sockaddr_in clientaddr, serveraddr;

    char buf_in[255];
    char buf_out[255];
    char* name;
    

    if (argc != 2)
    {
        printf("Usage : ./add_server [port]\n");
        printf("Example  : ./add_server 8080\n");
        exit(0);
    }
  
    state = 0;

    // internet 기반의 소켓 생성 (INET)
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error : ");
        exit(0);
    }
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(atoi(argv[1]));

    state = bind(server_sockfd , (struct sockaddr *)&serveraddr,
            sizeof(serveraddr));

    if (state == -1)
    {
        perror("bind error : ");
        exit(0);
    }

    state = listen(server_sockfd, 5);
    if (state == -1)
    {
        perror("listen error : ");
        exit(0);
    }
    // Server 
    printf("Now, We are just listening %s ports (Ctrl+c will stop server)...\n",argv[1]);

    while(1)
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr,
                               &client_len);

        if (client_sockfd == -1)
        {
            perror("Accept error : ");
            exit(0);
        }

        // greeting
        read(client_sockfd, buf_in, 255);
        printf("%s\n",buf_in);

        if (strncmp(buf_in, "Hello This is", 13) == 0) {
                greeted = 1;
                name = buf_in+14;
                
                strncpy(buf_out, "200 Welcome ",13);
                strncat(buf_out, name,241);
                strncat(buf_out,". What can I do for you?",25);

                write(client_sockfd, buf_out, 255);
        }
        else {
            strncpy(buf_out, "400 I'm sorry. Greeting is required.",255);
            write(client_sockfd,buf_out, 255);
        }

        while(1)
        {
            memset(buf_in, '\0', 255);
            memset(buf_out, '\0', 255);
            
            if (read(client_sockfd, buf_in, 255) <= 0)
            {
                close(client_sockfd);
                break;
            }

            // if client types 'quit'
            if (strncmp(buf_in, "quit",4) == 0)
            {
                strncpy(buf_out, "200 bye",255);
                printf("Client is disconnected.\n");
                write(client_sockfd, buf_out, 255);

                close(client_sockfd);
                exit(0);
            }

            strncpy(buf_out,"200 ok",6);

            printf("%s\n",buf_in); // print client's input
            write(client_sockfd, buf_out, 255);
            //printf("Send End\n");
        }
    }
    close(client_sockfd);
}
