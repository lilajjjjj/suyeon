#include "kvs.h"

// 키에 해당하는 값 검색
char* get(kvs_t* kvs, const char* key) {
    if (kvs == NULL || key == NULL) return NULL;

    node_t* current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}
