#!/usr/bin/python
import os
import time
import struct

fileNamePrefix = "./data/l1cGetInd.log"


def Check_dir(FileInfo):
    lineNum = 0
    eldFrameNum = 0
    eldSlotNum = 0
    newFrameNum = 0
    newSlotNum = 0
    with open(FileInfo, mode='r', encoding='utf-8') as f2read:
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
                newFrameNum = int(lineEle[2])
                newSlotNum = int(lineEle[4])
                # if (newFrameNum <= eldFrameNum) & (eldFrameNum != 1023 & newFrameNum != 0):
                if (newSlotNum != eldSlotNum + 1) & (eldSlotNum != 79 & newSlotNum != 0):
                    # print("\n")
                    print("ELE: " + str(lineNum) + "\t" + "MSN: " +
                          str((newFrameNum - eldFrameNum)*79 - eldSlotNum + newSlotNum) +
                          "\tEFS: " + str(eldFrameNum) + '\t' + str(eldSlotNum) +
                          "\tNFS: " + str(newFrameNum) + '\t' + str(newSlotNum))
                    # print("MSN: " + str((newFrameNum - eldFrameNum)*79 - eldSlotNum + newSlotNum))
                    # print("EFS: " + str(eldFrameNum) + ',' + str(eldSlotNum))
                    # print("NFS: " + str(newFrameNum) + ',' + str(newSlotNum))
                eldFrameNum = newFrameNum
                eldSlotNum = newSlotNum
                # print("FN:" + str(frameNum) + "," + "SN:" + str(slotNum))

            if len(line) <= 0:
                f2read.close()
                break
            line = f2read.readline()
            lineNum += 1
    return 0


if __name__ == "__main__":
    print("Processing...")
    ret = Check_dir(fileNamePrefix)
    if ret != 0:
        print("Check_dir error.")
    print("Done.")
