#include "kvs.h"

int main() {
    kvs_t *kvs = open();  // Skip List 초기화

    // query.dat 파일 열기
    FILE *queryFile = fopen("query.dat", "r");
    FILE *answerFile = fopen("answer.dat", "w");

    if (queryFile == NULL || answerFile == NULL) {
        perror("파일을 열 수 없습니다");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), queryFile)) {
        char operation[10], key[256], value[256];
        sscanf(line, "%[^,],%[^,],%s", operation, key, default_value);

        if (strcmp(operation, "put") == 0) {
            put(kvs, key, value);  // Skip List에 키-값 저장
        } else if (strcmp(operation, "get") == 0) {
            char *result = get(kvs, key);  // 키로 값 조회
            // 값이 존재하면 result, 없으면 기본값 value를 출력
            fprintf(answerFile, "%s\n", result ? result : default_value);
        }
    }

    fclose(queryFile);
    fclose(answerFile);
    kvs_close(kvs);  // 메모리 해제
    return 0;
}
