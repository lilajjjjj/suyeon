#include "kvs.h"

int main() {
    SkipList *list = create_skiplist(16, 0.5);

    // 1. 사전 데이터 삽입
    // 특정 키에 대해 사전에 값 저장 (예: put("tweet0", "customer985") 같은 방식)
    put(list, "tweet0", "customer985");  // 필요한 다른 키-값 쌍도 추가합니다.

    // 2. query.dat 파일 읽기
    FILE *queryFile = fopen("query.dat", "r");
    FILE *answerFile = fopen("answer.dat", "w");

    char line[256];
    while (fgets(line, sizeof(line), queryFile)) {
        char operation[10], key[256], default_value[256];
        sscanf(line, "%[^,],%[^,],%s", operation, key, default_value);

        if (strcmp(operation, "get") == 0) {
            char *result = get(list, key);
            // 키가 없으면 default_value 반환, 있으면 result 반환
            fprintf(answerFile, "%s: %s\n", key, result ? result : default_value);
        }
    }

    fclose(queryFile);
    fclose(answerFile);
    free_skiplist(list);
    return 0;
}
