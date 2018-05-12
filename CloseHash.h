#ifndef _CLOSEHASH_H_
#define _CLOSEHASH_H_

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef int KeyType;
typedef int ValueType;

enum Status
{
	EMPTY,
	EXITE,
	DELETE,
};
typedef struct HashNode {
	KeyType _key;
	ValueType _value;
	enum Status _status;
}HashNode;
typedef struct HashTable {
	HashNode * _table;
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