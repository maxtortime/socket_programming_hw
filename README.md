# Computer Network Homework #1: Remote calculator

> README.md 는 markdown 파일이고, homework_report.pdf 로 보셔도 이 문서와 똑같은 내용이 적혀있습니다. 

## Author 
* 학과: 미디어학과 
* 학번: 201122037 
* 성명: 김태환

## Introduction
Server와 Client가 서로 1:1로 연결되어, (2개 이상의 Client가 Server에 접속하는 건 구현하지 못함) 각자의 소켓으로 데이터를 주고 받게 된다. 먼저 Server와 Client가 인사를 하고, Client는 각종 사칙연산 명령을 Server에게 보내면 Server는 그걸 처리하여 결과를 Client에게 보내주는 프로그램이다. 이 과정에서 Client가 잘못된 명령을 보내면 Server가 역시 적절히 처리하여 어떤 것이 잘못됬는지 Client에게 메시지를 보내준다.

### Language and Development enviroments

* 언어 / 컴파일러: C언어 / gcc (GCC) 4.8.3 20140911 (Red Hat 4.8.3-9)
* OS: Server 와 Client 모두 CentOS 7 에서 테스트 완료.

### Program setting

* 201122037\_김태환.zip 파일을 다운로드한다.
* 압축파일을 풀면 다음과 같은 파일이 존재한다.

```sh
$ ls
client.c makefile README.md server.c
```
* 이때 쉘에 다음과 같이 입력한다.
```sh
$ make
$ ls
client  client.c  makefile  README.md server  server.c
```
* 그러면 위의 소스코드가 컴파일 되고, 이때 생긴 client 와 server가 각각 서버와 클라이언트의 실행파일이다.

## 프로그램 동작

### 서버 프로그램 실행
```sh
$ ./server 8080
Now, We are just listening 8080 ports (Ctrl+c will stop server)...
author: 201122037 Taehwan Kim
```
정상적으로 프로그램을 실행시키면 위처럼 출력되면서 계속 8080 port를 열어놓게 된다. 만약 프로그램 실행 시 포트번호를 주지 않았다면, 어떻게 포트 번호를 프로그램에 입력해야 하는지에 대한 안내메시지가 출력된다.
```sh
$ ./server
Usage : ./server [port]
Example  : ./server 8080
```
위에서 설명하는 것처럼 port 번호를 입력해주면, 정상적으로 서버가 동작하게 된다. Server 프로그램은 이렇게 실행만 시켜놓으면 딱히 입력을 한다거나 해줄 일은 크게 없다.

만약 이미 해당 port를 점유하고 있는 프로그램이 있었다면 Bind error가 발생한다.
```sh
$ ./server 8080
bind error : : Address already in use
```
이런 경우 다른 port 번호를 사용해주면 보통 해결된다.

### Client 프로그램 실행
```sh
$ ./client 127.0.0.1 8080
Welcome to socket calculation client program.
author: 201122037 Taehwan Kim
Please input your name. (length:~20)> 
```
Client 프로그램을 실행시키려면, 접속할 서버의 ip주소와 port 번호를 입력하면 된다. 그러면 위와 같이 안내 문구가 출력되면서 프로그램이 이름을 입력받게 된다. 이름을 입력하고 나면 정상적으로

### Greeting

Server를 올바로 실행하고, Client도 서버에 접속하였다면, 서로 메시지를 주고 받을 준비가 끝난 것이다. 그러나 Sever와 Client가 서로 연결은 됬지만, 이 프로그램은 Client가 먼저 Server에게 인사 메시지(Greeting)을 보내고 Server도 그에 따른 응답 인사를 해줘야 앞으로의 작업을 수행할 수 있다. Client가 Server에게 보내야 하는 Greeting 메시지의 형식은 다음과 같다.

> Hello This is {{name}}

{{name}}앞의 'Hello This is '는 대소문자가 구분되며 또한 각 어절 사이는 띄어쓰기 한 칸으로 되어있어야 한다.

> 즉, {{name}} 전 글자의 갯수가 정확히 **14개**여야 한다는 것이다.

Client 프로그램을 실행시키고 위에서처럼 이름을 입력했다면, 프로그램에서 Greeting 메시지를 어떻게 보내야 하는 지 알려준다.
```sh
Thanks. Connection with server is successful.
But you must greet with server.
If you want to greet with server.
then you should type to your shell like this...
Usage : name> Hello This is {{name}}
Example : Tom> Hello This is {{Tom}}
If you type 'quit', can disconnet with server and quit this program.
tkim>
```
맨 아래 방금 적은 이름이 보이는 shell에 프로그램의 지시대로 Greeting 메시지를 입력하면 된다. 
> shell의 > 와 사용자가 입력하는 첫 글자는 한 칸의 공백이 있으므로 주의해야 한다. 

또한 'quit'라고 치면 Server와의 연결이 끊어지고, 프로그램이 종료된다. 단, Greeting을 하지 않으면, Server는 Client와 연결됬다고 생각하지 않아서 꺼지지 않는다. 이건 나중에 자세히 설명하도록 한다. 물론 이 상테에서도 서버로 메시지를 보내는 것은 가능하다. 하지만, 아직 Greeting을 하지 않았으므로, Server는 오류를 Client에게 전송하게 된다.

예를 들어,
```sh
tkim> hello
server-> 400 I'm sorry. Greeting is required.
tkim> Hello
server-> 400 I'm sorry. Greeting is required.
tkim> hi?
server-> 400 I'm sorry. Greeting is required.
```
위의 Greeting 형식을 맞추지 않은 메시지에 대해서 Server가 전부 오류 메시지를 보내는 것을 확인할 수 있다. 즉, Greeting을 하지 않으면 정상적인 프로그램 이용이 불가능하다는 걸 알 수 있다. 이제 제대로 된 Greeting 메시지를 보내보자.
```sh
tkim> Hello This is tkim
server-> 200 Welcome tkim. What can I do for you?
 1) add  2) sub 3) mult 4) div ex) add 100 200
```
제대로 된 Greeting을 입력하니 Server에서도 반겨주며, 어떤 명령을 처리할 수 있는지 Client에게 알려주고 있다. 서버 프로그램에도 이제 Client가 보낸 메시지가 출력된다.
```sh
$ ./server 8080
Now, We are just listening 8080 ports (Ctrl+c will stop server)...
author: 201122037 Taehwan Kim
Hello This is tkim
```
### 계산 명령 수행

과제에서 제시한 명령을 모두 Server가 수행할 수 있다. 명령은 대소문자 구별을 하지 않는다. 또한 매개변수로 문자를 보내면 Server가 에러 메시지를 보내준다. 매개변수는 둘다 long integer이고, 범위는 limits.h 에 정의된 LONG\_MIN~LONG\_MAX 값이다. 명령을 보내는 형식은 다음과 같다. 

> {{operation}} {{long integer}} {{long integer}}

> (테스트 환경에서 man limits.h 확인 결과 LONG\_MIN = -2,147,483,647, LONG\_MAX = +2,147,483,647)

아래에 각 명령에 대한 설명과 함께 어떻게 사용하는지 예시도 자세히 나와있다.

#### ADD {{long integer}} {{long integer}}
```sh
tkim> ADD 100 200
server-> 200 Result 300
tkim> add 300 200
server-> 200 Result 500
tkim> aDD 100 500
server-> 200 Result 600
tkim> add 11111111 -22222211
server-> 200 Result -11111100
```
#### SUB {{long integer}} {{long integer}}
```sh
tkim> sub 100 100
server-> 200 Result 0
tkim> Sub 500 400
server-> 200 Result 100
tkim> sub 23923085 908098
server-> 200 Result 23014987
tkim> sub 0 -3
server-> 200 Result 3
```
#### MULT {{long integer}} {{long integer}}
```sh
tkim> mult 200 300
server-> 200 Result 60000
tkim> mult 123456789 123456789
server-> 200 Result 15241578750190521
tkim> mult -3 -3
server-> 200 Result 9
tkim> MULT -522324 5599
server-> 200 Result -2924492076
```
#### DIV {{long integer}} {{long integer}}
```sh
tkim> div 2384 235
server-> 200 Result 10
tkim> DIV 523 13
server-> 200 Result 40
tkim> div 0 2
server-> 200 Result 0
tkim> div 2 0
server-> 403 Parameter error: you divided by zero!
tkim> div 2345898250 89778
server-> 200 Result 26129
```
### 계산 명령 시 발생하는 각종 오류 정리

오류가 발생하더라도 Server나 Client는 종료되지 않고 지속적으로 메시지를 보내고 명령을 수행할 수 있다. Paramter가 2개를 초과하면 오류는 아니고 자연스럽게 앞 두 매개변수로만 계산하게 되어 있다.

#### 401 Unknown command 
Server가 수행할 수 없는 명령을 입력한 경우이다.
```sh
tkim> abc 100 200
server-> 401 Unknown command
tkim> dia 200 200
server-> 401 Unknown command
```
#### 402 Too few Parameters

매개변수를 적게 입력함.
```sh
tkim> a
server-> 402 Too few Parameters
tkim> add 3
server-> 402 Too few Parameters
tkim> div 3
server-> 402 Too few Parameters
```
#### 403 Parameter error

계산 값을 문자열로 넘겨줌.
```sh
tkim> add b b
server-> 403 Parameter error
tkim> add zero one
server-> 403 Parameter error
```
#### 403 Parameter error: you divided by zero!

0으로 나누려고 함.
```sh
tkim> div 2 0
server-> 403 Parameter error: you divided by zero!
tkim> DIV 2525 0
server-> 403 Parameter error: you divided by zero!
```
#### 500 Server overflow

계산 범위를 초과한 값을 입력
```sh
tkim> add 9999999999999999999 999999999999999999999
server-> 500 Server overflow
```
### 프로그램 종료

Client가 quit를 입력하면 프로그램이 종료된다. 이 경우 Greeting을 완료한 상태라면 Server 프로그램도 같이 종료하지만, Greeting이 되지 않았다면 Server는 계속 켜져있다.

예를 들어, 한창 잘 작동하고 있는 경우이다. 
* Client
```sh
tkim> add 9999999999999999999 999999999999999999999
server-> 500 Server overflow
tkim> quit
200 bye
$
```
* Server

```sh
add 9999999999999999999 999999999999999999999
server-> 500 Server overflow
quit
Client is disconnected.
$
```
이처럼 client가 quit라고 입력한 순간 server에는 'Client is disconnected'라고 뜨면서 Server 역시 종료한다. 그러나 greeting을 하지 않고, client가 quit를 친 경우는
```sh
tkim> quit
400 I'm sorry. Greeting is required.
$
```
이렇게 서버에 영향을 미치지 못하고, client 프로그램만 종료되는 것을 볼 수 있다.
> Greeting 은 필수!

## 프로그램 구조 분석
이번엔 server와 client의 소스코드의 구조를 분석해보면서 어떤 식으로 돌아가는 프로그램인지 알아보고자 한다. 부분 부분 이 보고서에 소스를 첨부하면서 설명하도록 하겠다.
### Server
서버 프로그램은 크게
1. 소켓 생성 및 주소 설정
2. 변수 초기화 및 Greeting check
3. client의 명령 parsing
4. 계산 후 client에게 결과 보내기

로 이루어져 있다고 볼 수 있다.
#### 소켓 생성 및 주소 설정
```c
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
```
소켓을 생성하고 서버 주소 초기화 및 port 번호 지정을 한다.
#### Greeting check
```c
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
```
buf_in과 Hello This is 문자열을 비교해서 같으면 greeting을 완료했다 판단하고 client에게 메시지를 보내주고, greeted 가 0이면서 메시지도 틀렸으면 에러메시지를 보내준다.

#### Client 명령 Parsing
```c
tk = strtok(buf_in," ");
            
while (tk != NULL && i < TRANS_SIZE) {
    to_upp(tk); //  Token must be upper-case.
    transaction[i] = tk;
    i++; // count how many parameters
    tk = strtok(NULL," ");
}
```
strtok() 를 사용해서 client가 보낸 문자열을 공백 단위로 토큰으로 만들었다. 그리고 i라는 변수는 parameter가 몇 개인지 가지고 있게 된다. to_upp()은 직접 만든 문자열을 알파벳 대문자로 전부 바꿔주는 함수이다.
```c
void to_upp(char* stra)
{
    while(*stra) {
        *stra = toupper(*stra);
        stra++;
    }
}
```
다음 위의 transcation array의 0번째와 1번쨰 element만 가지고 계산을 수행하게 된다.
```c
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
```
strtol()을 사용하여 아주 쉽게 문자열로 된 숫자를 적절히 변환할 수 있었다. atoi를 쓰려고 했는데 strtol은 숫자가 아닌 부분을 다시 포인터로 넘겨주기도 하고, 덕분에 포인터의 반환값을 보고 그 문자열의 상태를 알 수 있었다.

생각해보면 위의 lptr과 rptr을 간접 참조한 값은 char 값인데 만약 그게 0이 아니라면 그게 문자(ascii 코드값)라는 말이다. 그러므로 0이면 숫자이고 0이 아니면 아스키 코드이므로 해당 문자열이 문자인지 숫자인지 파악할 수 있었다. 다음 else if 문은 단순히 lv 와 rv 값이 long의 범위를 넘어서지 않았나 확인하는 것이다. strtol()은 overflow가 일어나면 그냥 LONG_MAX나 LONG_MIN을 가지게 되므로 저렇게 비교해도 괜찮다고 man page에 적혀 있었다.

> long int strtol(const char *nptr, char **endptr, int base);

```c
/* Check for various possible errors */
if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
       || (errno != 0 && val == 0)) {
   perror("strtol");
   exit(EXIT_FAILURE);
}
```

다음은 단순히 order와 "ADD", "SUB" 등의 문자열을 비교해서 각각의 사칙연산을 수행하고, sprintf()를 이용해 buf_out에 해당 값을 적게 된다. 그리고 맨 마지막에 cleint에게 메시지를 보내는 건 한 번만 수행하고, (맨 위에 메시지를 보내는 건 모두 sprintf()를 사용함)
```c
write(client_sockfd, buf_out, BUF_SIZE);
```
메시지를 보낸 후에는 다시 루프를 돌아서 지금까지의 과정을 다시 수행하여 client와 연속적으로 통신하게 되는 것이다.

### Client
Client 프로그램은
1. 소켓 생성 및 주소 설정
2. 변수 초기화 및 user에게 메시지 입력 받음
3. Server에게 메시지를 보내고, Server의 응답을 다시 console에 출력함
의 구조로 이루어져 있다.

#### 소켓 생성 및 주소 설정
```c
client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
clientaddr.sin_family = AF_INET;
clientaddr.sin_addr.s_addr = inet_addr(argv[1]);
clientaddr.sin_port = htons(atoi(argv[2]));

client_len = sizeof(clientaddr);
```
Server와 크게 다를 건 없지만, 아까 Server는 모든 ip에 대한 접속을 유지해야 하므로 INADDR_ANY를 썼지만, Client는 Server하고만 통신하면 되므로 사용자가 입력하는 서버 주소값을 사용했다는 걸 알 수 있다.

#### User에게 메시지를 입력 받고 Server로 보내
```
// Greeting

 printf("Welcome to socket calculation client program.\n");
 printf("author: 201122037 Taehwan Kim\n");
 printf("Please input your name. (length:~20)> ");
 fgets(name, NAME_SIZE, stdin);

 /* Remove trailing newline, . */
 if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
    name[strlen (name) - 1] = '\0';

printf("Thanks. Connection with server is successful.\n");
printf("But you must greet with server.\n");
printf("If you want to greet with server.\n");
printf("then you should type to your shell like this...\n");
printf("Usage : name> Hello This is {{name}}\n");
printf("Example : Tom> Hello This is {{Tom}}\n");
printf("If you type 'quit', can disconnet with server and quit this program.\n");

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
```
User에게 지시를 하고 user의 이름을 받아서 shell에 표시해주고 계속 입력을 받고 메시지를 Server로 보내고 받는 부분이다. fgets로 입력 받았을 때 자꾸 \n이 삽입되어서 제거하는 코드를 삽입하였다.

### socket 닫기
> close(client_sockfd);

Server나 Client 모두 마지막에 사용한 소켓을 닫아주지 않으면 곤란한 경우가 생길 것이다. 계속 테스트하면서도 bind error나 accept error가 자주 발생하여 어떤 원인인지 몰랐다가 프로그램을 강제 종료해서 socket이 제대로 닫히지 않아서 그렇다는 걸 깨달았다. 이후 프로그램이 발전하면서 종료할 때 소켓을 닫도록 해주어서 Accept error는 더 이상 나지 않았다.



