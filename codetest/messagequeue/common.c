#include "common.h"

void reportAndExit(const char* msg)
{
    perror(msg);
    exit(-1);
}



/* End of this file. */