#include "kvs.h"

// 메모리 해제 함수 (이름 변경)
int kvs_close(kvs_t* kvs) {
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
