#include "kvs.h"

// Skip List에 키-값 쌍을 저장하는 함수
int put(kvs_t* kvs, const char* key, const char* value) {
    SkipList *list = kvs->list;
    SkipListNode *update[list->maxLevel + 1];
    SkipListNode *current = list->header;

    // 키의 위치를 찾기 위해 레벨별로 탐색
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // 0 레벨에서 키를 찾음
    current = current->forward[0];

    // 키가 이미 존재할 경우 값을 업데이트
    if (current && strcmp(current->key, key) == 0) {
        free(current->value);
        current->value = strdup(value);
        return 0;
    }

    // 새로운 노드를 삽입
    int newLevel = random_level(list);
    if (newLevel > list->level) {
        for (int i = list->level + 1; i <= newLevel; i++) {
            update[i] = list->header;
        }
        list->level = newLevel;
    }

    SkipListNode *newNode = (SkipListNode *)malloc(sizeof(SkipListNode));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->forward = (SkipListNode **)malloc(sizeof(SkipListNode *) * (newLevel + 1));

    for (int i = 0; i <= newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    return 0;
}
