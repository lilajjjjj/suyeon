#include "kvs.h"

int main() {
    SkipList *list = create_skiplist(16, 0.5);
    FILE *queryFile = fopen("query.dat", "r");
    FILE *answerFile = fopen("answer.dat", "w");

    char line[256];
    while (fgets(line, sizeof(line), queryFile)) {
        char operation[10], key[256], value[256];
        sscanf(line, "%[^,],%[^,],%s", operation, key, value);

        if (strcmp(operation, "put") == 0) {
            put(list, key, value);
        } else if (strcmp(operation, "get") == 0) {
            char *result = get(list, key);
            fprintf(answerFile, "%s: %s\n", key, result ? result : value);
        }
    }

    fclose(queryFile);
    fclose(answerFile);
    free_skiplist(list);
    return 0;
}
