cmake_minimum_required(VERSION 3.1)

set(L2_PRJ_TYPE "L2_PC_PRJ")
set(L2_PLAT_TYPE "L2_WITH_DPDK")

if((${L2_PRJ_TYPE} STREQUAL "L2_BD_PRJ") AND (${L2_PLAT_TYPE} STREQUAL "L2_WITH_DPDK"))
    message(STATUS "L2Usm_CM_Case1")
	set(DIR_LIB_EXT_SRCS ./Src/L2UsmDpdk.c ./Src/L2UsmSokt.c)
elseif(${L2_PRJ_TYPE} STREQUAL "L2_PC_PRJ" AND (${L2_PLAT_TYPE} STREQUAL "L2_WITH_DPDK"))
	message(STATUS "L2Usm_CM_Case2")
	set(DIR_LIB_EXT_SRCS ./Src/L2UsmDpdk.c)
else()
	message(WARNING "L2Usm_CM_CaseE")
	message(WARNING "Invalid env for USM")
endif()

message(STATUS "L2Usm_ENV1：${L2_PRJ_TYPE}")
message(STATUS "L2Usm_ENV2：${L2_PLAT_TYPE}")