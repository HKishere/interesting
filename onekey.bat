@echo off
REM �˽ű�����һ������������\�ͻ���\��ý��

set bin_path="e:\SVN_XIANAN\XAzysx_BHF3.0\trunk_207\Code(v4.1)\bin"
set media_path="e:\���\iVMS-4200 Stream Media Server\4.0.0.7"

echo ��ʼһ������
echo ===============

echo ��������������?
tasklist|findstr -i "CentreSrverD.exe"
if ERRORLEVEL 1 (
	echo û������!
	echo ��������������...
	start "" %bin_path%\CentreSrverD.exe
)

echo �ͻ�����������?
tasklist|findstr -i "APPD.exe"
if ERRORLEVEL 1 (
	echo û������!
	echo ���������ͻ���...
	start "" %bin_path%\APPD.exe
)

echo ��ý����������?
tasklist|findstr -i "StreamServerApp.exe"
if ERRORLEVEL 1 (
	echo û������!
	echo ����������ý��...
	start "" %media_path%\StreamServerApp.exe
)

echo �������!
echo ==============
echo ����������رտͻ��˺ͷ�����

pause

taskkill /f /im "CentreSrverD.exe"
taskkill /f /im "APPD.exe"

