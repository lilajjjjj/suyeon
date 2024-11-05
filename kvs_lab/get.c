#include "kvs.h"

// Skip List에서 키로 값을 조회하는 함수
char* get(kvs_t* kvs, const char* key) {
    SkipList *list = kvs->list;
    SkipListNode *current = list->header;

    // 키를 탐색하여 레벨별로 위치 찾기
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    // 키가 있으면 값을 반환, 없으면 NULL 반환
    if (current && strcmp(current->key, key) == 0) {
        return current->value;
    }

    return NULL;
}
