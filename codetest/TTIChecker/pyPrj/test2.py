#!/usr/bin/python
import os
import time
import struct
import sys

#fileNamePrefix = "../data/l1cGetInd.log"


def Check_dir(FileInfo):
    lineNum = 0
    eldFrameNum = 0
    eldSlotNum = 0
    eldTime = 0
    newFrameNum = 0
    newSlotNum = 0
    newTime = 0
    print("FileInfo = " + FileInfo)
    with open(FileInfo, mode='r', encoding='utf-8') as f2read: # 
        line = f2read.readline()
        lineNum += 1
        while line:
            # print(line)
            lineEle = line.replace(':', '\t')
            lineEle = lineEle.replace('\t\t', '\t')
            lineEle = lineEle.split('\t')
            # print(len(lineEle))
            if len(lineEle) > 0:
                # for ele in range(len(lineEle)):
                l1Ele = lineEle[0].split('-')
                newTime = int(l1Ele[1])

                print("Time gap = " + str(newTime - eldTime))

                eldTime = newTime
                # print("FN:" + str(frameNum) + "," + "SN:" + str(slotNum))

            if len(line) <= 0:
                f2read.close()
                break
            line = f2read.readline()
            lineNum += 1
    return 0


if __name__ == "__main__":
    print("Processing...")
    print("sys.argc = ", len(sys.argv))
    
    for arg in range(len(sys.argv)):
        print("argv = " + sys.argv[arg])
    
    fileNamePrefix = sys.argv[1]
    
    ret = Check_dir(fileNamePrefix)
    if ret != 0:
        print("Check_dir error.")
    print("Done.")
