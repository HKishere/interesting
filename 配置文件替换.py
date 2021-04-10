import os
import glob
import shutil
# 遍历当前目录下所有文件和子文件夹文件
print("将此程序放在原边海防目录下, 填入新安装的边海防目录即可复制原来的配置文件")
distpath = input("填入新安装的目录:")
allPyFile = glob.glob('**/*.py', recursive=True)
for pyFile in allPyFile:
    shutil.copyfile(pyFile, distpath + "\\" + pyFile)

