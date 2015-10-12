#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void to_upp(char* stra);

int main(int argc, char **argv)
{
    const int BUF_SIZE = 255, GREETING_SIZE = 50, TRANS_SIZE = 20;
    int server_sockfd, client_sockfd;
    int state, client_len;
    int pid;
    int i = 0;
    int greeted = 0;

    struct sockaddr_in clientaddr, serveraddr;

    char buf_in[BUF_SIZE];
    char buf_out[BUF_SIZE];
    char* name;
    char* tk;
    char * order;
    char* transaction[TRANS_SIZE];
    // left value and right value when calculation.
    long lv = 0;
    long rv = 0; 
    char* lptr = NULL;
    char* rptr = NULL;
    

    if (argc != 2)
    {
        printf("Usage : ./server [port]\n");
        printf("Example  : ./server 8080\n");
        exit(0);
    }
  
    state = 0;

    // INET 기반의 소켓 생성
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error : ");
        exit(0);
    }

    memset(&serveraddr,0,sizeof(serveraddr)); // 서버 주소 초기화
    serveraddr.sin_family = AF_INET; // ipv4 사용
    // 주소를 알맞게 변환함.
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serveraddr.sin_port = htons(atoi(argv[1])); 

    state = bind(server_sockfd , (struct sockaddr *)&serveraddr,
            sizeof(serveraddr)); // socket에 ip 주소와 port 지정

    if (state == -1)
    {
        perror("bind error : ");
        exit(0);
    }

    state = listen(server_sockfd, 5); // socket의 연결을 확인
    if (state == -1)
    {
        perror("listen error : ");
        exit(0);
    }
    // Server 프로그램 메시지 출력
    printf("Now, We are just listening %s ports (Ctrl+c will stop server)...\n", argv[1]);
    printf("author: 201122037 Taehwan Kim\n");

    while(1)
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr,
                               &client_len); // socket의 연결을 승인함.

        if (client_sockfd == -1)
        {
            perror("Accept error : ");
            exit(0);
        }

        while(1)
        {
            // 메시지 버퍼 초기화 
            i = 0;
            memset(buf_in, '\0', BUF_SIZE);
            memset(buf_out, '\0', BUF_SIZE);
            
            if (read(client_sockfd, buf_in, BUF_SIZE) <= 0)
            {
                close(client_sockfd);
                break;
            }
            // greeting checking
            if (greeted ==0) {
                if (strncmp(buf_in, "Hello This is ",13)==0) 
                {
                    greeted = 1;
                    name = buf_in+14;
                    printf("%s\n",buf_in);
                    sprintf(buf_out,"200 Welcome %s. What can I do for you?\n 1) add  2) sub 3) mult 4) div ex) add 100 200",name);
                }
                else  {  
                    sprintf(buf_out,"400 I'm sorry. Greeting is required.");
                }
            }
            else {
                printf("%s\n",buf_in);
                tk = strtok(buf_in," ");
            
                while (tk != NULL && i < TRANS_SIZE) {
                    to_upp(tk); //  Token must be upper-case.
                    transaction[i] = tk;
                    i++; // count how many parameters
                    tk = strtok(NULL," ");
                }

                if (i < 3 && strncmp(transaction[0], "QUIT",4) != 0)
                {
                    // parameter가 2개 미만인 경우
                    // 하지만 quit를 입력한 경우 정상적으로 종료되어야 한다.
                    sprintf(buf_out,"402 Too few Parameters");
                }
                else if(strncmp(transaction[0], "QUIT",4) == 0)
                {
                    // if client sends 'quit'
                    sprintf(buf_out,"200 bye");    
                    printf("Client is disconnected.\n");
                    write(client_sockfd, buf_out, BUF_SIZE);

                    close(client_sockfd);
                    exit(0);
                }
                else 
                {
                    lv = strtol(transaction[1],&lptr,10);
                    rv = strtol(transaction[2],&rptr,10);
                    order = transaction[0];

                    if (*lptr != 0  || *rptr!= 0 ) {
                        // When first character of left or right parameter
                        // is 0 then they are not integers. 
                        sprintf(buf_out,"403 Parameter error");
                    }
                    else if ((lv == LONG_MAX || lv  == LONG_MIN) || 
                        (rv == LONG_MIN || rv== LONG_MAX)) {
                        sprintf(buf_out,"500 Server overflow");
                    }
                    else 
                    {
                        // All parameters are good, then do Transaction.
                        if (strncmp(order,"ADD",3)==0) 
                            sprintf(buf_out,"200 Result %ld", lv + rv);
                        else if (strncmp(order,"MULT",3)==0) 
                            sprintf(buf_out,"200 Result %ld",lv * rv);
                        else if (strncmp(order,"SUB",3)==0) 
                            sprintf(buf_out,"200 Result %ld",lv - rv);
                        else if (strncmp(order,"DIV",3)==0)
                        {
                            if (rv==0)
                                sprintf(buf_out,"403 Parameter error: you divided by zero!");
                            else
                                sprintf(buf_out,"200 Result %ld",lv / rv);
                        }
                        else
                            sprintf(buf_out,"401 Unknown command");
                    }   
                }    
            }
            write(client_sockfd, buf_out, BUF_SIZE); 
            
        }
    }
    close(client_sockfd);
}

void to_upp(char* stra)
{
    while(*stra) {
        *stra = toupper(*stra);
        stra++;
    }
}
