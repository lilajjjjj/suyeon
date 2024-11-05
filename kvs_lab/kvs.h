#ifndef KVS_H
#define KVS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// 기존 코드와 구조체 정의는 유지
// ...

// 함수 선언 (함수 이름 변경)
kvs_t* open();
int kvs_close(kvs_t* kvs); // 이름을 kvs_close로 변경
int put(kvs_t* kvs, const char* key, const char* value); // return -1 if failed.
char* get(kvs_t* kvs, const char* key); // return NULL if not found.

#endif // KVS_H
