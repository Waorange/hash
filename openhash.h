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

//����-1��ʾ���ֵ���� ����0��ʾ����ɹ�
int HashInset(HashTable * ht, KeyType key, ValueType value);

//�����ҵ���λ�õ�ַ û���ҵ����ؿ�
HashNode * HashFind(HashTable * ht, KeyType key);

//ɾ���ɹ�����0��ʧ�ܷ���-1
int HashRemove(HashTable * ht, KeyType key);

void HashDestory(HashTable * ht);

//���ڽ���������Ϊ����
size_t GetNextPrimeNum(size_t capcity);

#endif