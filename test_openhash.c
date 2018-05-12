#include "openhash.h"
#include <time.h>

static void _HashPrint_int(HashTable * ht)
{
	assert(ht);
	for (size_t i = 0; i < ht->_capcity; i++)
	{
		printf("%3d:  ", i + 1);
		HashNode * cur = ht->_table[i];
		while (cur)
		{
			printf("[%d %d]->", cur->_key, cur->_value);
			cur = cur->_next;
		}
		printf("[NULL]\n");
	}
}

//static void _HashPrint_string(HashTable * ht)
//{
//	assert(ht);
//	for (size_t i = 0; i < ht->_capcity; i++)
//	{
//		printf("%3d:  ", i + 1);
//		HashNode * cur = ht->_table[i];
//		while (cur)
//		{
//			printf("[%s %d]->", cur->_key, cur->_value);
//			cur = cur->_next;
//		}
//		printf("[NULL]\n");
//	}
//}

void testHash_int()
{
	HashTable HT;
	HashInit(&HT, GetNextPrimeNum(50));

	//≤Â»Î
	for (int i = 0; i < 53;)
	{
		if (HashInset(&HT, rand() % 1000, i) == 0)
		{
			i++;
		}
	}
	_HashPrint_int(&HT);
	printf("\n\n");

	//µ⁄54∏ˆΩ¯––¿©»› ∏∫‘ÿ“Ú◊”Œ™1 ±¿©»›
	printf("¿©»›\n");
	HashInset(&HT, 50, 53);
	HashInset(&HT, 124, 54);
	_HashPrint_int(&HT);
	printf("\n\n");

	//…æ≥˝≤‚ ‘
	printf("…æ≥˝50\n");
	HashRemove(&HT, 50);
	_HashPrint_int(&HT);
	printf("\n\n");

	printf("…æ≥˝ £”‡»´≤ø\n");
	for (int i = 0; i < 1000; i++)
	{
		HashRemove(&HT, i);
	}
	_HashPrint_int(&HT);
	printf("\n\n");

	// Õ∑≈ø’º‰
	HashDestory(&HT);
}

//void testHash_string()
//{
//	HashTable HT;
//	HashInit(&HT, GetNextPrimeNum(50));
//
//	KeyType arr[] = { "abcd", "sdas", "sdsw", "sfdae", "sfefe", "ferr", "ewwes" };
//	for (size_t i = 0; i < sizeof(arr) / sizeof(KeyType); ++i)
//	{
//		HashInset(&HT, arr[i], i);
//	}
//	_HashPrint_string(&HT);
//	printf("\n\n");
//
//	//…æ≥˝≤‚ ‘
//	printf("…æ≥˝50\n");
//	HashRemove(&HT, "abcd");
//	_HashPrint_string(&HT);
//	printf("\n\n");
//
//	// Õ∑≈ø’º‰
//	HashDestory(&HT);
//}

int main()
{
	srand((unsigned int)time(NULL));
	testHash_int();
	//testHash_string();
	system("pause");
	return 0;
}