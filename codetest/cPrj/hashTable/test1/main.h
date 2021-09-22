#ifndef _MAIN_H_
#define _MAIN_H_

#define DataType int
#define M 30

typedef struct HashNode
{
	DataType data;    //存储值 
	int isNull;           //标志该位置是否已被填充 
}HashTable;




#endif