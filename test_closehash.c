#include "CloseHash.h"


static void _HashPrint(HashTable * ht)
{
	for (size_t i = 0; i < ht->_capcity; i++)
	{
		if (ht->_table[i]._status == EXITE)
		{
			printf("[%d %d] ", ht->_table[i]._key, ht->_table[i]._value);
		}
		else if(ht->_table[i]._status == DELETE)
		{
			printf("[DELETE] ");
		}
		else
		{
			printf("[NULL] ");
		}
	}
}

void testHash()
{
	HashTable HT;
	HashInit(&HT, GetNextPrimeNum(38));

	for (int i = 0; i < 38;)
	{
		if (HashInset(&HT, rand() % 1000, i) == 0)
		{
			i++;
		}
	}
	_HashPrint(&HT);
	printf("\n\n");

	//第39个进行扩容 ( 38 * 10 / 53 == 7) 负载因子为7时扩
	HashInset(&HT, 50, 39);
	HashInset(&HT, 124, 40);
	_HashPrint(&HT);
	printf("\n\n");

	//删除测试
	HashRemove(&HT, 50);
	_HashPrint(&HT);
	printf("\n\n");

	for (int i = 0; i <= 1000; i++)
	{
		HashRemove(&HT, i);
	}
	_HashPrint(&HT);
	printf("\n\n");

	//释放空间
	HashDestory(&HT);
}

int main()
{
	testHash();
	system("pause");
	return 0;
}
