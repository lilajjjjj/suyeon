#ifndef KVS_H
#define KVS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 노드 구조체 정의
struct node {
    char key[100];
    char* value;
    struct node* next;
};  
typedef struct node node_t;

// 키-값 저장소 구조체 정의
struct kvs {
    struct node* db; // 데이터베이스 (연결 리스트)
    int items;       // 저장된 데이터 수
};
typedef struct kvs kvs_t;

// 함수 선언
kvs_t* open();                     // 데이터베이스 초기화
int kvs_close(kvs_t* kvs);         // 데이터베이스 메모리 해제 (이름 충돌 방지를 위해 kvs_close로 변경)
int put(kvs_t* kvs, const char* key, const char* value); // 키-값 쌍 저장
char* get(kvs_t* kvs, const char* key);                  // 키로 값 검색

#endif // KVS_H
