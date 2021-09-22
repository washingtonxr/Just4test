#include <stdio.h>
#include <string.h>
#include "main.h"

int main()
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    do {
        for(i = 0; i < TIP_NUM; i++) {
            j = i;
            printf("j = %d\n", j);
        }
        printf("Round = %d\n", k++);
    }while(1);
}
