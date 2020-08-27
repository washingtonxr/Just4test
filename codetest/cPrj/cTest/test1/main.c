#include <stdio.h>
#include <string.h>
#include <unistd.h>

//#include <gperftools/profiler.h>
static void domath()
{
  int result = 1000000;
  for (int i = 0 ; i < 1; ++i) {
    result += 100;
    result -= 10;
    result *= 100;
    result /= 100;
    result %= 10;
    result ^= 10;
    result != 10;
    result = ~10;
    result &= 10;
    result |= 10;
  }
}

//test.c 
static void longa() 
{ 
  int i,j; 
  for(i = 0; i < 1; i++) 
  j=i; //am I silly or crazy? I feel boring and desperate. 
}

static void longb() 
{ 
  int i,j; 
  for(i = 0; i < 1; i++) 
  j=i; //am I silly or crazy? I feel boring and desperate. 
}

static void longc() 
{ 
  int i,j; 
  for(i = 0; i < 1; i++) 
  j=i; //am I silly or crazy? I feel boring and desperate. 
}

void foo2() 
{ 
  int i; 
  for(i=0 ; i < 1; i++) 
       longb(); 
}

void foo3() 
{ 
  int i; 
  for(i=0 ; i < 1; i++) 
       longc();
}

void foo1() 
{ 
  int i; 
  for(i = 0; i< 1; i++){ 
    longa();
    domath();
    usleep(100); 
  }
}

int main(void) 
{
  //ProfilerStart("mainCapture.prof");
  foo1();
  foo2();
  foo3();
  //ProfilerStop();
}
