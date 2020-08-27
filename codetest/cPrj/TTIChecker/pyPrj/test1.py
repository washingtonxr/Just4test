#!/usr/bin/python
import os
import time
import struct
import sys

#fileNamePrefix = "../data/l1cGetInd.log"
def Check_legend():
    print("++++++++++++++++++++++++++++++++++++++++++++++++++")
    print("Legend:")
    print("ELE :" + '\t' + "Error line ID in log file.")
    print("DFT :" + '\t' + "Difference in timestamp.")
    print("DFS :" + '\t' + "Difference in slots.")
    print("EFS :" + '\t' + "Eld frame ID and slot ID.")
    print("NFS :" + '\t' + "New frame ID and slot ID.")
    print("++++++++++++++++++++++++++++++++++++++++++++++++++")

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
                detalTime = newTime - eldTime
                newFrameNum = int(lineEle[2])
                newSlotNum = int(lineEle[4])
                # if (newFrameNum <= eldFrameNum) & (eldFrameNum != 1023 & newFrameNum != 0):
                if (newSlotNum != eldSlotNum + 1) & (eldSlotNum != 79 & newSlotNum != 0):
                    # print("\n")
                    print("ELE: " + str(lineNum) + "\t" + "MSN: " +
                          str((newFrameNum - eldFrameNum)*80 - eldSlotNum + newSlotNum) +
                          "\tEFS: " + str(eldFrameNum) + '\t' + str(eldSlotNum) +
                          "\tNFS: " + str(newFrameNum) + '\t' + str(newSlotNum) +
                          "\tT12: " + str(int(lineEle[6], 16) - int(lineEle[5], 16)) +
                          "\tT3: " + str(int(lineEle[7], 16))
                          )
                    # print("MSN: " + str((newFrameNum - eldFrameNum)*79 - eldSlotNum + newSlotNum))
                    # print("EFS: " + str(eldFrameNum) + ',' + str(eldSlotNum))
                    # print("NFS: " + str(newFrameNum) + ',' + str(newSlotNum))
                eldFrameNum = newFrameNum
                eldSlotNum = newSlotNum
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
    
    # Show legend.
    Check_legend()
    
    # Check each line of log.
    ret = Check_dir(fileNamePrefix)
    if ret != 0:
        print("Check_dir error.")
    print("Done.")
