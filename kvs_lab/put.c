#include "kvs.h"

// 키-값 쌍 저장
int put(kvs_t* kvs, const char* key, const char* value) {
    if (kvs == NULL || key == NULL || value == NULL) return -1;

    node_t* current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // 기존 키에 대한 값 업데이트
            free(current->value);
            current->value = strdup(value);
            return 0;
        }
        current = current->next;
    }

    // 새로운 노드 추가
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) return -1;

    strncpy(new_node->key, key, sizeof(new_node->key) - 1);
    new_node->key[sizeof(new_node->key) - 1] = '\0';
    new_node->value = strdup(value);
    new_node->next = kvs->db;
    kvs->db = new_node;
    kvs->items++;

    return 0;
}
