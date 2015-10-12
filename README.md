# 컴퓨터 네트워크 과제: 원격 계산기
### 작성자 
* 학과: 미디어학과 
* 학번: 201122037
* 성명:  김태환

### 사용 언어 및 개발환경
* 언어 / 컴파일러: C언어 / gcc (GCC) 4.8.3 20140911 (Red Hat 4.8.3-9)
* OS: Server 와 Client 모두 CentOS 7 에서 테스트 완료.

### 프로그램 동작 개요
서버와 클라이언트가 1대1로 연결되어 서로의 소켓으로 데이터를 주고 받게 된다. 서버가 자신의 소켓을 열고 대기하고 있으면, 클라이언트는 자신에 shell에 명령을 입력하여 서버와 통신하게 된다. 서버와 클라이언트 프로그램을 사용하는 자세한 방법은 아래에서 설명하도록 하고, 지금은 실행 파일을 만드는 법을 설명하도록 한다.
* 압축파일을 풀면 다음과 같은 파일이 존재한다.
``` sh
$ ls
client.c makefile README.md server.c
```
* 이때 쉘에 다음과 같이 입력한다.
```sh
$ make
$ ls
client  client.c  makefile  README.md server  server.c
```
* 그러면 위의 코드가 컴파일 되고, 이때 생긴 client 와 server가 각각 서버와 클라이언트의 실행파일이다.

### 서버 프로그램 동작
```sh
$ ./server 8080
Now, We are just listening 8080 ports (Ctrl+c will stop server)...
author: 201122037 Taehwan Kim
```
정상적으로 프로그램을 실행시키면 위처럼 출력되면서 계속 8080 port를 열어놓게 된다..만약 프로그램 실행 시 포트번호를 주지 않았다면, 어떻게 포트 번호를 프로그램에 입력해야 하는지에 대한 안내메시지가 출력된다.
```sh
$ ./server
Usage : ./server [port]
Example  : ./server 8080
```
위에서 설명하는 것처럼 port 번호를 입력하여주면, 정상적으로 서버가 동작하게 된다. Server는 이제 Client와 지속적으로 메시지를 주고 받으며 Client가 보내는 명령을 처리하게 된다. 


Dillinger is a cloud-enabled, mobile-ready, offline-storage, AngularJS powered HTML5 Markdown editor.

  - Type some Markdown on the left
  - See HTML in the right
  - Magic

Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site][df1]

> The overriding design goal for Markdown's
> formatting syntax is to make it as readable
> as possible. The idea is that a
> Markdown-formatted document should be
> publishable as-is, as plain text, without
> looking like it's been marked up with tags
> or formatting instructions.

This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

### Version
3.2.0

### Tech

Dillinger uses a number of open source projects to work properly:

* [AngularJS] - HTML enhanced for web apps!
* [Ace Editor] - awesome web-based text editor
* [Marked] - a super fast port of Markdown to JavaScript
* [Twitter Bootstrap] - great UI boilerplate for modern web apps
* [node.js] - evented I/O for the backend
* [Express] - fast node.js network app framework [@tjholowaychuk]
* [Gulp] - the streaming build system
* [keymaster.js] - awesome keyboard handler lib by [@thomasfuchs]
* [jQuery] - duh

And of course Dillinger itself is open source with a [public repository][dill]
 on GitHub.

### Installation

You need Gulp installed globally:

```sh
$ npm i -g gulp
```

```sh
$ git clone [git-repo-url] dillinger
$ cd dillinger
$ npm i -d
$ mkdir -p downloads/files/{md,html,pdf}
$ gulp build --prod
$ NODE_ENV=production node app
```

### Plugins

Dillinger is currently extended with the following plugins

* Dropbox
* Github
* Google Drive
* OneDrive

Readmes, how to use them in your own application can be found here:

* [plugins/dropbox/README.md] [PlDb]
* [plugins/github/README.md] [PlGh]
* [plugins/googledrive/README.md] [PlGd]
* [plugins/onedrive/README.md] [PlOd]

### Development

Want to contribute? Great!

Dillinger uses Gulp + Webpack for fast developing.
Make a change in your file and instantanously see your updates!

Open your favorite Terminal and run these commands.

First Tab:
```sh
$ node app
```

Second Tab:
```sh
$ gulp watch
```

(optional) Third:
```sh
$ karma start
```

### Todos

 - Write Tests
 - Rethink Github Save
 - Add Code Comments
 - Add Night Mode

License
----

MIT


**Free Software, Hell Yeah!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does it's job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [@thomasfuchs]: <http://twitter.com/thomasfuchs>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [marked]: <https://github.com/chjj/marked>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [keymaster.js]: <https://github.com/madrobby/keymaster>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>
   
   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]:  <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>

