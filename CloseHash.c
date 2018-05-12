#include "CloseHash.h"

static size_t _HashFanc(HashTable * ht, KeyType key);
static void _CheckCapcity(HashTable * ht);
static size_t BKDRHash(const char * str);
     
//Hash容量素数表 (取素数主要为了减少Hash冲突)
#define PRIMESIZE 28
static const unsigned long _PrimeList[PRIMESIZE] = {
	53ul,         97ul,         193ul,       389ul,       769ul,         
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,         
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,         
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,         
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,         
	1610612741ul, 3221225473ul, 4294967291ul };

size_t  GetNextPrimeNum(size_t capcity)
{
	assert(capcity > 0);
	for (int i = 0; i < PRIMESIZE; ++i)
	{
		if (_PrimeList[i] >= capcity)
		{
			return _PrimeList[i];
		}
	}
	return 0;
}

static void _CheckCapcity(HashTable * ht)
{
	assert(ht);
	if (ht->_size * 10 / ht->_capcity == 7)
	{
		HashTable newht;
		HashInit(&newht, GetNextPrimeNum(ht->_capcity + 1));
		for (size_t i = 0; i < ht->_capcity; ++i)
		{
			if (ht->_table[i]._status == EXITE)
			{
				HashInset(&newht, ht->_table[i]._key, ht->_table[i]._value);
			}
		}
		free(ht->_table);
		ht->_table = newht._table;
		ht->_size = newht._size;
		ht->_capcity = newht._capcity;
	}
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
	//KeyType为char*
	//return BKDRHash(key) % ht->_capcity;

	//KeyType为int时
	return key % ht->_capcity;
}

void HashInit(HashTable * ht, size_t capcity)
{
	assert(ht && capcity > 0);
	ht->_capcity = capcity;
	ht->_table = (HashNode *)malloc(sizeof(HashNode) * capcity);
	assert(ht->_table);
	for (size_t i = 0; i < ht->_capcity; ++i)
	{
		ht->_table[i]._status = EMPTY;
	}
	ht->_size = 0;
}

//返回-1表示这个值存在 返回0表示插入成功
int HashInset(HashTable * ht, KeyType key, ValueType value)
{
	assert(ht);
	_CheckCapcity(ht); //检查容量如果容量不足对其扩容
	size_t index = _HashFanc(ht, key);  //通过hash函数寻找需要存储的位置

	//线性探测   
	//
	//while (ht->_table[index]._status == EXITE)
	//{
	//	if (ht->_table[index]._key == key)
	//	{
	//		return -1;
	//	}
	//	index++;
	//	if (index == ht->_capcity)
	//	{
	//		index = 0;
	//	}
	//}
	//

	//二次探测
	size_t i = 1, _index = index;
	while (ht->_table[index]._status == EXITE)
	{
		if (ht->_table[index]._key == key)
		{
			return -1;
		}
		index = _index + i * i;
		i++;
		if (index >= ht->_capcity)
		{
			index = 0;
		}
	}

	ht->_table[index]._key = key;
	ht->_table[index]._status = EXITE;
	ht->_table[index]._value = value;
	ht->_size++;
	return 0;
}

//返回找到的位置地址 没有找到返回空
HashNode * HashFind(HashTable * ht, KeyType key)
{
	assert(ht);
	size_t index = _HashFanc(ht, key);
	while (ht->_table[index]._status != EMPTY)
	{
		if (ht->_table[index]._key == key)
		{
			return &ht->_table[index];
		}
		index++;
		if (index == ht->_capcity)
		{
			index = 0;
		}
	}
	return NULL;
}

//删除成功返回0，失败返回-1
int HashRemove(HashTable * ht, KeyType key)
{
	assert(ht);
	HashNode * node = HashFind(ht, key);
	if (node != NULL)
	{
		node->_status = DELETE;
		ht->_size--;
		return 0;
	}
	return -1;
}

void HashDestory(HashTable * ht)
{
	assert(ht);
	free(ht->_table);
	ht->_table = NULL;
	ht = NULL;
}

