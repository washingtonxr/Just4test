#include "main.h"

void* Memcpy(void *des,const void *src,size_t len)
{
    size_t size=len/4;//计算有多少bit位，用整数一次性拷贝，效率高
    size_t mod=len%4; //剩下的bit位
    int Len=size;    //作个临时变量，后面会用到

    //把他们都转化成整数，这样一次性就可以拷贝四个字节
    int *Des=(int*)des;
    int *SRC=(int*)src;

    while(size--)
        *Des++=*SRC++;

    //没有多余的字节，即已经拷贝完成
    if(mod==0)
            return des;

    char *t=(char*)src;
    t+=Len*sizeof(int);//让t前面已经拷贝的下一个字节

    char *key=(char*)des;
    key+=Len*sizeof(int);//同理

    //cout<<"des :"<<(char*)des<<"  src:"<<(char*)src<<endl;
    while(mod--) //拷贝剩余的字节
    {
        *key++=*t++;
    }
    //cout<<"memcpy  des :"<<(char*)des<<"  src:"<<(char*)src<<endl;
    return des;
}

int mem_test(void)
{
    double usedTime = 0;
    double KByteRate = 0;
    struct timespec timeStart, timeEnd;
    unsigned int i = 0, j = 0;

    for(i = 0; i < TRY_TIME; i++)
    {
        unsigned int dLen = sizeof(char)*1024*pow(2, i);
        //printf("sizeof(char) = %d\n", sizeof(char));
        //printf("dLen = %d\n", dLen);

        char *sData = (char *)malloc(dLen);
        char *dData = (char *)malloc(dLen);
#if 1
#if 0
        unsigned int CopyTime = (unsigned int)(dLen);
        CopyTime /= FOURKB_BLOCK;
        unsigned int LetfBytes = dLen%FOURKB_BLOCK;
        char *sPrt = dData;
        char *dPrt = sData;
        printf("CopyTime = %d, LeftBytes = %d\n", CopyTime, LetfBytes);

        memset(sData, 0x55, dLen);
        clock_gettime(CLOCK_MONOTONIC, &timeStart);//start time
        if(dLen > FOURKB_BLOCK){
            for(unsigned int k = 0; k < CopyTime; k++)
            {
                memcpy(sPrt, dPrt, FOURKB_BLOCK);
                sPrt += FOURKB_BLOCK;
                dPrt += FOURKB_BLOCK;
            }
            /* Handle let bytes. */
            if(LetfBytes > 0){
                memcpy(sPrt, dPrt, LetfBytes);
            }
        }else{
            memcpy(dData, sData, dLen);
        }
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);//end time
        usedTime += (timeEnd.tv_sec - timeStart.tv_sec)*1000.0 + \
                    (timeEnd.tv_nsec - timeStart.tv_nsec)/1000000.0; //ms
        KByteRate = ((dLen/1024) / (usedTime))/1024;
        printf("T(%02d)\t%d\t%f\t%f\n", i, dLen/1024, usedTime, KByteRate);
#else
        /* No optimize. */
        memset(sData, 0x55, dLen);
        clock_gettime(CLOCK_MONOTONIC, &timeStart);//start time
        //memcpy(dData, sData, dLen);
        Memcpy(dData, sData, dLen);
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);//end time
        usedTime += (timeEnd.tv_sec - timeStart.tv_sec)*1000.0 + \
                    (timeEnd.tv_nsec - timeStart.tv_nsec)/1000000.0; //ms
        KByteRate = ((dLen/1024) / (usedTime))/1024;
        printf("X(%02d)\t%d\t%f\t%f\n", i, dLen/1024, usedTime, KByteRate);
#endif
#endif
#if 0
        printf("sData:\n");
        // Print sData.
        for(j = 0; j < 32; j++)
        {
            printf("%d ", *(char *)(sData + j));
        }
        printf("\n");

        printf("dData:\n");
        // Print dData.
        for(j = 0; j < 32; j++)
        {
            printf("%d ", *(char *)(dData + j));
        }
        printf("\n");
#endif
        free(sData);
        free(dData);
    }
    printf("Time\tKB\tUsetime(ms)\tSpeed(MB/s)\n");
    return 0;
}

int main(unsigned int argc, char **argv)
{
    mem_test();

    return 0;
}

/* End of this file. */
