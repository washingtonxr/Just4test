//c_unix.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <unistd.h>

#if 0
#define UNIX_DOMAIN "./psctrl_l1c"//"/tmp/UNIX.domain"
#else
#define UNIX_DOMAIN "/tmp/psctrl_l1c"//"/tmp/UNIX.domain"
#endif

#define BUFSIZ 40
#define HEADER 4

#define nrl1c_init_req                  40 /* @_Nrl1cInitReq                   */
#define nrl1c_init_cnf                  41 /* @_Nrl1cInitCnf                   */
#define nrl1c_cell_setup_req            42 /* @_Nrl1cCellSetupReq              */
#define nrl1c_cell_setup_cnf            43 /* @_Nrl1cCellSetupCnf              */
#define nrl1c_cell_delete_req           44 /* @_Nrl1cCellDeleteReq             */
#define nrl1c_cell_delete_cnf           45 /* @_Nrl1cCellDeleteCnf             */
#define nrl1c_destroy_req               46 /* @_Nrl1cDestroyReq                */
#define nrl1c_destroy_cnf               47 /* @_Nrl1cDestroyCnf                */
#define nrl1c_rf_recfg_req              48 /* @_Nrl1cRfRecfgReq                */
#define nrl1c_rf_recfg_cnf              49 /* @_Nrl1cRfRecfgCnf                */
#define nrl1c_rf_set_tx_power_req       50 /* @_Nrl1cRfSetTxPowerReq           */
#define nrl1c_rf_set_tx_power_cnf       51 /* @_Nrl1cRfSetTxPowerCnf           */
#define nrl1c_phy_reconfig_req          52 /* @_Nrl1cPhyReconfigReq            */
#define nrl1c_phy_reconfig_cnf          53 /* @_Nrl1cPhyReconfigCnf            */

unsigned char test_payload[40] = {0x78,0x27,0x8f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x48,0x45,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x39,0x75,0xa0,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//unsigned char test_payload2[112] = {0x10,0x2c ,0x8f,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00,0x5f,0x69,0x64,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x38,0xd1,0x9e,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x6d,0x73,0x67,0x5f,0x68,0x36,0xd1,0x9e,0xff,0xff,0x00,0x00,0x40,0x35,0xd1,0x9e,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x35,0xd1,0x9e,0xff,0xff,0x00,0x00,0xf0,0x34,0xd1,0x9e,0xff,0xff,0x00,0x00,0x70,0x2f,0xd1,0x9e,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x2f,0xd1,0x9e,0xff,0xff,0x00,0x00};
unsigned char test_payload2[] = {0x0a,0x02,0x08,0x02,0x1a,0x74,0x08,0x08,0x10,0x08,0x18,0x80,0x01,0x20,0x80,0x01,0x28,0x04,0x3a,0x18,0x08,0x81,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xa0,0xb7,0xd1,0x0c,0x28,0xe0,0xc4,0x88,0x0e,0x30,0x64,0x3a,0x18,0x08,0x82,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xa0,0xae,0xd7,0x0b,0x28,0xe0,0xbb,0x8e,0x0d,0x30,0x64,0x3a,0x18,0x08,0x84,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xc0,0xa6,0xd2,0x11,0x28,0x80,0xb4,0x89,0x13,0x30,0x64,0x3a,0x18,0x08,0x85,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xe0,0xbb,0x8e,0x0d,0x28,0xb0,0xac,0xc2,0x0d,0x30,0x64,0x22,0x43,0x08,0x01,0x10,0x04,0x18,0x81,0x02,0x22,0x3a,0x0a,0x0b,0x08,0x01,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x01,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x02,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x03,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x28,0x01,0x3a,0x00,0x42,0x00,0x4a,0x9d,0x01,0x0a,0x04,0x12,0x02,0x08,0x01,0x12,0x55,0x12,0x53,0x0a,0x1a,0x12,0x18,0x08,0xea,0x07,0x1a,0x13,0x08,0x01,0x10,0x03,0x32,0x0d,0x10,0x10,0x18,0xf4,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x12,0x35,0x08,0x64,0x10,0xf0,0xfe,0xa7,0x04,0x1a,0x05,0x00,0x00,0x00,0x01,0x00,0x22,0x05,0x00,0x00,0x00,0x42,0x00,0x28,0x64,0x30,0xf0,0xfe,0xa7,0x04,0x3a,0x05,0x00,0x00,0x00,0x01,0x00,0x42,0x05,0x00,0x00,0x00,0x42,0x00,0x50,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x1a,0x3e,0x12,0x0a,0x12,0x08,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x00,0x12,0x0a,0x12,0x08,0x12,0x00,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x0e,0x12,0x0c,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x14,0x12,0x08,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x00,0x12,0x08,0x12,0x00,0x12,0x04,0x08,0x80,0x80,0x01,0x52,0x1a,0x12,0x18,0x08,0xea,0x07,0x1a,0x13,0x08,0x01,0x10,0x03,0x32,0x0d,0x10,0x10,0x18,0xf4,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x5a,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x20,0x38,0x30,0x20,0x38,0x30,0x20,0x30,0x31,0x20,0x31,0x32,0x20,0x30,0x30,0x20,0x31,0x32,0x20,0x30,0x38,0x20,0x31,0x32,0x20,0x30,0x30,0x20,0x31,0x32,0x20,0x30,0x34,0x20,0x30,0x38,0x20,0x38,0x30,0x20,0x38,0x30,0x20,0x30,0x31,0x20,0x35,0x32,0x20,0x31,0x61,0x20,0x31,0x32,0x20,0x31,0x38,0x20,0x30,0x38,0x20,0x65,0x61,0x20,0x30,0x37,0x20,0x31,0x61,0x20,0x31,0x33,0x20,0x30,0x38,0x20,0x30,0x31,0x20,0x31,0x30,0x20,0x30,0x33,0x20,0x33,0x32,0x20,0x30,0x64,0x20,0x31,0x30,0x20,0x31,0x30,0x20,0x31,0x38,0x20,0x66,0x34,0x20,0x66,0x63,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x66,0x66,0x20,0x30,0x31,0x20,0x35,0x61,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x31,0x35,0x20,0x30,0x34,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x30,0x30,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x33,0x38,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x38,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x31,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x34,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x33,0x38,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x38,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x31,0x20,0x32,0x30,0x20,0x33,0x35,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x36,0x31,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x36,0x35,0x20,0x36,0x31,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x37,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x36,0x31,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x38,0x20,0x32,0x30,0x20,0x33,0x30,0x20,0x33,0x31,0x20,0x32,0x30,0x20,0x33,0x31,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x30,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x30,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x32,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x32,0x20,0x33,0x30,0x20,0x32,0x30,0x20,0x33,0x33,0x20,0x33,0x33,0x20,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa1,0xfe,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char test_payload3[] = {0x0a,0x02,0x08,0x02,0x1a,0x74,0x08,0x08,0x10,0x08,0x18,0x80,0x01,0x20,0x80,0x01,0x28,0x04,0x3a,0x18,0x08,0x81,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xa0,0xb7,0xd1,0x0c,0x28,0xe0,0xc4,0x88,0x0e,0x30,0x64,0x3a,0x18,0x08,0x82,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xa0,0xae,0xd7,0x0b,0x28,0xe0,0xbb,0x8e,0x0d,0x30,0x64,0x3a,0x18,0x08,0x84,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xc0,0xa6,0xd2,0x11,0x28,0x80,0xb4,0x89,0x13,0x30,0x64,0x3a,0x18,0x08,0x85,0x02,0x10,0x9c,0xff,0xff,0xff,0x0f,0x18,0xe0,0x12,0x20,0xe0,0xbb,0x8e,0x0d,0x28,0xb0,0xac,0xc2,0x0d,0x30,0x64,0x22,0x43,0x08,0x01,0x10,0x04,0x18,0x81,0x02,0x22,0x3a,0x0a,0x0b,0x08,0x01,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x01,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x02,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x0a,0x0d,0x08,0x01,0x10,0x03,0x18,0x80,0x80,0x01,0x20,0xe0,0xbb,0xb6,0x0d,0x28,0x01,0x3a,0x00,0x42,0x00,0x4a,0x9d,0x01,0x0a,0x04,0x12,0x02,0x08,0x01,0x12,0x55,0x12,0x53,0x0a,0x1a,0x12,0x18,0x08,0xea,0x07,0x1a,0x13,0x08,0x01,0x10,0x03,0x32,0x0d,0x10,0x10,0x18,0xf4,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x12,0x35,0x08,0x64,0x10,0xf0,0xfe,0xa7,0x04,0x1a,0x05,0x00,0x00,0x00,0x01,0x00,0x22,0x05,0x00,0x00,0x00,0x42,0x00,0x28,0x64,0x30,0xf0,0xfe,0xa7,0x04,0x3a,0x05,0x00,0x00,0x00,0x01,0x00,0x42,0x05,0x00,0x00,0x00,0x42,0x00,0x50,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x1a,0x3e,0x12,0x0a,0x12,0x08,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x00,0x12,0x0a,0x12,0x08,0x12,0x00,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x0e,0x12,0x0c,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x14,0x12,0x08,0x12,0x04,0x08,0x80,0x80,0x01,0x12,0x00,0x12,0x08,0x12,0x00,0x12,0x04,0x08,0x80,0x80,0x01,0x52,0x1a,0x12,0x18,0x08,0xea,0x07,0x1a,0x13,0x08,0x01,0x10,0x03,0x32,0x0d,0x10,0x10,0x18,0xf4,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0x5a,0x00};

void *thread(void *x)  
{   
    int cmd;
    unsigned char i;
    char recv_buf[1024];
    int new_fd = *((int*)x);
    unsigned int ret;
    unsigned int cnt = 0;
    unsigned int dlen;

    while(1)
    {
        ret = recv(new_fd, recv_buf, HEADER, 0);
        if(ret > 0){
            printf("========= Received msg(%d) ==========>>>\n", cnt++);
            for(i = 0; i < HEADER; i++){
                printf("%02x ", recv_buf[i]);
            }
            dlen = recv_buf[1];
            dlen <<=8;
            dlen += recv_buf[0];
            printf("\n==dlen(%d)==>\n", dlen);
            ret = 0;
            ret = recv(new_fd, &recv_buf[HEADER], dlen, 0);
            if(ret > 0){
                printf("recv payload:\n");
                for(i = 0; i < ret; i++){
                    printf("%02x ", recv_buf[4+i]);
                }
            }
            printf("\n========= Received msg End ==========\n");
        }
    }
    return NULL;  
}

int main(void)
{
    int connect_fd;
    int ret;
    char snd_buf[1024];
    unsigned int i;
    static struct sockaddr_un srv_addr;

    //creat unix socket
    connect_fd = socket(PF_UNIX,SOCK_STREAM,0);
    if(connect_fd<0)
    {
        perror("cannot create communication socket");
        return 1;
    }   
    srv_addr.sun_family=AF_UNIX;
    strcpy(srv_addr.sun_path,UNIX_DOMAIN);

    //connect server
    ret = connect(connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    if(ret==-1)
    {
        perror("cannot connect to the server");
        close(connect_fd);
        return 1;
    }
    //create a thread.
    pthread_t ntid;
    pthread_create(&ntid,NULL,thread,&connect_fd);

    //send info to server
    unsigned int cnt = 0;
    while(1){
        memset(snd_buf, 0, sizeof(snd_buf));
        //strcpy(snd_buf, "message from client");
#if 0

#else
        unsigned int sdlen = sizeof(test_payload3);
        printf("Sizeof payload: %d\n", sdlen);
        snd_buf[0] = sdlen;   //Low
        snd_buf[1] = sdlen >> 8;   //High
        snd_buf[2] = 53;    //group
        snd_buf[3] = nrl1c_cell_setup_req;  //nrl1c_init_req;    //
#if 0
        for(i = 0; i < BUFSIZ; i++)
            snd_buf[4+i] = i;
#else
        memcpy(&snd_buf[4], test_payload3, sizeof(test_payload3));
#endif
#endif
        ret = write(connect_fd, snd_buf, sizeof(test_payload3) + HEADER);
        printf("ret = %d\n", ret);
        printf("Send time:%d\n", cnt++);

        printf("========= Send msg ==========>>>\n");
        for(i = 0; i < sizeof(test_payload3) + HEADER; i++){
            printf("%02x ", snd_buf[i]);
        }
        printf("\n========= Send msg End ==========\n");
#if 0
        close(connect_fd);
#endif
        usleep(100000);
    }

    close(connect_fd);
    return 0;
}