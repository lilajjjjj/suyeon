#include <stdio.h>
#include <string.h>
#include "kvs.h"

int main() {
    FILE *query_file = fopen("query.dat", "r");
    FILE *answer_file = fopen("answer.dat", "w");
    char operation[10], key[100], value[100];

    if (!query_file || !answer_file) {
        perror("파일을 열 수 없습니다.");
        return 1;
    }

    // kvs 객체 생성
    kvs_t kvs;
    open(&kvs); // kvs 초기화

    while (fscanf(query_file, "%[^,],%[^,],%s\n", operation, key, value) != EOF) {
        if (strcmp(operation, "put") == 0) {
            put(&kvs, key, value);  // kvs 객체 전달
        } else if (strcmp(operation, "get") == 0) {
            char *result = get(&kvs, key);  // kvs 객체 전달
            if (result) {
                fprintf(answer_file, "get,%s,%s\n", key, result);
            } else {
                fprintf(answer_file, "get,%s,NOT_FOUND\n", key);
            }
        }
    }

    close(&kvs); // kvs 객체 정리

    fclose(query_file);
    fclose(answer_file);
    return 0;
}

