#include "kvs.h"

int main() {
    kvs_t *kvs = open();  // 데이터베이스 초기화

    // query.dat 파일 열기
    FILE *queryFile = fopen("query.dat", "r");
    FILE *answerFile = fopen("answer.dat", "w");

    if (queryFile == NULL || answerFile == NULL) {
        perror("파일을 열 수 없습니다");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), queryFile)) {
        char operation[10], key[256], default_value[256];
        sscanf(line, "%[^,],%[^,],%s", operation, key, default_value);

        if (strcmp(operation, "get") == 0) {
            char *result = get(kvs, key);
            // 데이터가 없으면 출력하지 않음
            if (result) {
                fprintf(answerFile, "%s: %s\n", key, result);
            }
        }
    }

    fclose(queryFile);
    fclose(answerFile);
    kvs_close(kvs);  // 메모리 해제 (함수 이름 변경)
    return 0;
}
