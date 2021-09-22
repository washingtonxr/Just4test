#ifndef MAIN_H
#define MAIN_H

typedef struct _IMSG_HEADER_T{
    unsigned int fd;
    unsigned char len_low;
    unsigned char len_high;
    unsigned char group;
    unsigned char id;
    unsigned char test1;
    unsigned char test2;
    unsigned char test3;
    unsigned char test4;
    unsigned int testa;
    unsigned int testb;
    unsigned int testc;
    unsigned int testd;
}iMsg_Header_T;


typedef struct _IMSG_PACKAGE_T{
    iMsg_Header_T header;
    unsigned char *payload;
    unsigned int crc;
}iMsg_Package_T;

typedef struct _IMSG_PACKAGE_T2{
    iMsg_Header_T header;
    unsigned char *payload;
    unsigned int crc;
    unsigned char test1;
}iMsg_Package_T2;

#endif
