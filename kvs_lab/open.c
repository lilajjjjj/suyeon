#include "kvs.h"

// 데이터베이스 초기화
kvs_t* open() {
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));
    if (kvs == NULL) return NULL;
    kvs->db = NULL;
    kvs->items = 0;
    return kvs;
}

// 데이터베이스 메모리 해제
int close(kvs_t* kvs) {
    if (kvs == NULL) return -1;
    
    node_t* current = kvs->db;
    while (current != NULL) {
        node_t* temp = current;
        current = current->next;
        free(temp->value);  // 값의 메모리를 해제
        free(temp);          // 노드의 메모리를 해제
    }
    
    free(kvs);  // kvs_t 구조체 메모리 해제
    return 0;
}
