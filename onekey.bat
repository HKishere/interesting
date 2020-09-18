@echo off
REM 此脚本可以一键启动服务器\客户端\流媒体

set bin_path="e:\SVN_XIANAN\XAzysx_BHF3.0\trunk_207\Code(v4.1)\bin"
set media_path="e:\软件\iVMS-4200 Stream Media Server\4.0.0.7"

echo 开始一键启动
echo ===============

echo 服务器启动了吗?
tasklist|findstr -i "CentreSrverD.exe"
if ERRORLEVEL 1 (
	echo 没有启动!
	echo 正在启动服务器...
	start "" %bin_path%\CentreSrverD.exe
)

echo 客户端启动了吗?
tasklist|findstr -i "APPD.exe"
if ERRORLEVEL 1 (
	echo 没有启动!
	echo 正在启动客户端...
	start "" %bin_path%\APPD.exe
)

echo 流媒体启动了吗?
tasklist|findstr -i "StreamServerApp.exe"
if ERRORLEVEL 1 (
	echo 没有启动!
	echo 正在启动流媒体...
	start "" %media_path%\StreamServerApp.exe
)

echo 启动完毕!
echo ==============
echo 输入任意键关闭客户端和服务器

pause

taskkill /f /im "CentreSrverD.exe"
taskkill /f /im "APPD.exe"

