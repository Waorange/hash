#ifndef _OPENHASH_H_
#define _OPENHASH_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int KeyType;
typedef int ValueType;

typedef struct HashNode {
	KeyType _key;
	ValueType _value;
	struct HashNode * _next;
}HashNode;

typedef struct HashTable {
	HashNode ** _table;
	size_t _size;
	size_t _capcity;
}HashTable;

void HashInit(HashTable * ht, size_t capcity);

//返回-1表示这个值存在 返回0表示插入成功
int HashInset(HashTable * ht, KeyType key, ValueType value);

//返回找到的位置地址 没有找到返回空
HashNode * HashFind(HashTable * ht, KeyType key);

//删除成功返回0，失败返回-1
int HashRemove(HashTable * ht, KeyType key);

void HashDestory(HashTable * ht);

//用于将容量设置为素数
size_t GetNextPrimeNum(size_t capcity);

#endif