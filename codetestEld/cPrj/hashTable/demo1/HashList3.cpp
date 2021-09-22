#include "HashList3.h"

int main(int argc, char const *argv[])
{
	HashTable *ht = new HashTable();
	const char* key[]={"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                        "k", "l","m", "n", "o", "p", "q", "r", "s", "t", 
                        "u", "v", "w", "x", "y", "z"};
	const char* value[]={"1","2", "3", "3", "4", "5", "6", "7", "8", "9", "10", 
                        "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", 
                        "21", "22", "23", "24", "25", "26"};
	for (int i = 0; i < 26; ++i)
	{
		ht->install(key[i],value[i]);
	}
	ht->display();
	return 0;
}