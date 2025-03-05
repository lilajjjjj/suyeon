#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 16

int main(int argc, char* argv[])
{
    int ifd, ofd;
    char* buff;
    ssize_t nreads;

    if(argc < 2) {
        fprintf(stderr, "No arguments\n");
        return 1;
    }

    // 입력 파일 열기
    ifd = open(argv[1], O_RDONLY);
    if (ifd < 0) {
        fprintf(stderr, "Failed to open input file %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    // 출력 파일을 지정한 경우, `dup2`를 사용해 표준 출력을 리다이렉트
    if(argc == 4 && strcmp(argv[2], "into") == 0) {
        ofd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (ofd < 0) {
            fprintf(stderr, "Failed to open output file %s: %s\n", argv[3], strerror(errno));
            close(ifd);
            return 1;
        }
        // 표준 출력을 ofd로 리다이렉트
        if (dup2(ofd, STDOUT_FILENO) < 0) {
            fprintf(stderr, "Failed to redirect output: %s\n", strerror(errno));
            close(ifd);
            close(ofd);
            return 1;
        }
        close(ofd); // `ofd`는 더 이상 필요 없으므로 닫기
    }

    // 버퍼 할당
    buff = (char*) malloc(sizeof(char) * BUFF_SIZE);
    if (!buff) {
        fprintf(stderr, "Failed to allocate memory\n");
        close(ifd);
        return 1;
    }

    // 파일을 읽어 표준 출력 또는 지정된 출력 파일로 쓰기
    while((nreads = read(ifd, buff, BUFF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buff, nreads) != nreads) {
            fprintf(stderr, "Write error: %s\n", strerror(errno));
            free(buff);
            close(ifd);
            return 1;
        }
    }
    
    if (nreads < 0) {  // read 오류가 발생한 경우
        fprintf(stderr, "Read error: %s\n", strerror(errno));
    }

    free(buff);
    close(ifd);
    return 0;
}

