#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define LISTENQ 1024
#define MAXLINE 1024

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char buffer[MAXLINE];
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port>\n", argv[0]);
        exit(1);
    }

    // 소켓 생성
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    // 서버 주소 구조체 초기화
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    // 소켓 바인딩
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }
    // 클라이언트 연결 대기
    if (listen(listenfd, LISTENQ) < 0) {
        perror("Listen failed");
        exit(1);
    }
    printf("Waiting for request ...\n");
    while (1) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if (connfd < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Connected to %s\n", inet_ntoa(cliaddr.sin_addr));

        // 데이터 송수신
        while ((n = read(connfd, buffer, MAXLINE)) > 0) {
            buffer[n] = '\0';
            printf("server received %d bytes: %s", n, buffer);
            write(connfd, buffer, n);
        }
        close(connfd);
    }
    close(listenfd);
    return 0;
}

