import os
import glob
import shutil
# 遍历当前目录下所有文件和子文件夹文件
print("欢迎使用炸鸡写的配置文件转移工具ヽ(✿ﾟ▽ﾟ)ノ")
print("把本程序放在原边海防目录下, 按提示填入新安装的边海防目录即可复制原来的配置文件~")
print("一定要放在原边海防目录下, 如果不是请退出")
distpath = input("好的让我们开始吧~请填入新安装的目录:")
allIniFile = glob.glob('**/*.ini', recursive=True)
for iniFile in allIniFile:
    shutil.copyfile(iniFile, distpath + "\\" + iniFile)

input("搞定了!按回车Enter键退出...")
