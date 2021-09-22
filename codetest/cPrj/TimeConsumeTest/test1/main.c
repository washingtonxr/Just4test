#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double time_diff_usec(struct timeval bgn, struct timeval end)
{
    return (double)(end.tv_sec - bgn.tv_sec) * 1000000 + (double)(end.tv_usec - bgn.tv_usec);
}

int main(int argc, char * argv[])
{
    struct timeval bgn;
    struct timeval end;
    struct timeval *pbgn = &bgn;
    struct timeval *pend = &end;
    double diff = 0;
    double min = 100000;
    double max = 0;
    double sum = 0;
    int maxi = -1;

    if (argc != 2){
        printf("请输入次数\n");
    }
    int count = atoi(argv[1]);

    for (int i = 0; i < count; i++){
        gettimeofday(pbgn, NULL); //开始之间
        gettimeofday(pend, NULL); //结束时间

        diff = time_diff_usec(bgn, end); //开始时间与结束时间的差值
        if (diff < min){
            min = diff; // 记录最小差值
        }
        else if (diff > max){
            maxi = i;
            max = diff; // 记录最大差值
        }
        sum += diff;
    }
    printf("avg = %f, max = %f, maxi = %d, min = %f\n", sum / count, max, maxi, min);
}
