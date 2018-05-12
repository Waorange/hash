#include "openhash.h"

//Hash容量素数表 (取素数主要为了减少Hash冲突)
#define PRIMESIZE  28      
static const unsigned long _PrimeList[PRIMESIZE] = { 
	53ul,         97ul,         193ul,       389ul,       769ul,         
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,         
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,         
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,         
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,         
	1610612741ul, 3221225473ul, 4294967291ul };

static HashNode * _BuyHashNode(KeyType key, ValueType value);
static size_t BKDRHash(const char * str);
static size_t _HashFanc(HashTable * ht, KeyType key);

static HashNode * _BuyHashNode(KeyType key, ValueType value)
{
	HashNode * node = (HashNode *)malloc(sizeof(HashNode));
	node->_key = key;
	node->_value = value;
	node->_next = NULL;
	return node;
}

static size_t BKDRHash(const char * str) 
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;      
	while (*str) 
	{ 
		hash = hash * seed + (*str++); 
	}      
	return (hash & 0x7FFFFFFF);
}

static size_t _HashFanc(HashTable * ht, KeyType key)
{
	assert(ht);
	//KeyType为字符串时
	//return BKDRHash(key) % ht->_capcity;

	//KeyType为整型时
	return key % ht->_capcity;
}

size_t GetNextPrimeNum(size_t capcity)
{
	assert(capcity > 0);
	for (size_t i = 0; i < PRIMESIZE; ++i)
	{
		if (_PrimeList[i] >= capcity)
		{
			return _PrimeList[i];
		}
	}
	return -1;
}

static void _CheckCapcity(HashTable * ht)
{
	assert(ht);
	if (ht->_size == ht->_capcity)
	{
		HashTable newht;
		HashInit(&newht, GetNextPrimeNum(ht->_capcity + 1));
		for (size_t i = 0; i < ht->_capcity; ++i)
		{
			HashNode * cur = ht->_table[i];
			while (cur)
			{
				//计算扩容后新的位置
				size_t index = _HashFanc(&newht, cur->_key);

				HashNode * next = cur->_next;

				//头插
				cur->_next = newht._table[index];
				newht._table[index] = cur;

				cur = next;
			}
		}
		free(ht->_table);
		ht->_table = newht._table;
		ht->_size = newht._size;
		ht->_capcity = newht._capcity;
	}
}

void HashInit(HashTable * ht, size_t capcity)
{
	assert(ht && capcity > 0);
	ht->_capcity = capcity;
	ht->_table = (HashNode **)malloc(sizeof(HashNode *) * ht->_capcity);
	assert(ht->_table);
	for (size_t i = 0; i < ht->_capcity; ++i)
	{
		ht->_table[i] = NULL;
	}
	ht->_size = 0;
}

int HashInset(HashTable * ht, KeyType key, ValueType value)
{
	assert(ht);
	_CheckCapcity(ht);
	int index = _HashFanc(ht, key);
	HashNode * cur = ht->_table[index];
	while (cur)
	{
		if (cur->_key == key)
		{
			return -1;
		}
		cur = cur->_next;
	}
	HashNode * node = _BuyHashNode(key, value);

	//头插
	node->_next = ht->_table[index];
	ht->_table[index] = node;
	ht->_size++;
	return 0;
}

HashNode * HashFind(HashTable * ht, KeyType key)
{
	assert(ht);
	size_t index = _HashFanc(ht, key);
	HashNode * cur = ht->_table[index];
	while (cur)
	{
		if (cur->_key == key)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

int HashRemove(HashTable * ht, KeyType key)
{
	assert(ht);
	size_t index = _HashFanc(ht, key);
	HashNode * cur = ht->_table[index];
	HashNode * prev = NULL;
	while (cur)
	{
		if (cur->_key == key)
		{
			if (prev == NULL)
			{
				free(cur);
				ht->_table[index] = NULL;
			}
			else
			{
				prev->_next = cur->_next;
				free(cur);
			}
			ht->_size--;
			return 0;
		}
		prev = cur;
		cur = cur->_next;
	}
	return -1;
}


void HashDestory(HashTable * ht)
{
	assert(ht);
	HashNode * cur = NULL;
	for (size_t i = 0; i < ht->_capcity; ++i)
	{
		cur = ht->_table[i];
		while (cur)
		{
			HashNode * next = cur->_next;
			free(cur);
			cur = next;
		}
	}
	free(ht->_table);
	ht = NULL;
}