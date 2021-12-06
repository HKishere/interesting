#pragma once
#ifndef __SerialInterface_H_
#define __SerialInterface_H_
#include <Windows.h>
#include <string>
#include <vector>
#include <thread>

struct IMSGCBSERIAL
{
	virtual void OnRecvDataSerial(void *pBuf, int nLen) = 0;
};

class SerialCtl
{
public:
	SerialCtl();
	~SerialCtl();
public:
	//打开串口,并配置
	BOOL OpenCOM(const char* strSerialName, DWORD cBaudRate, BYTE cParity, unsigned char cByteSize, unsigned char cStopBits);

	//设置缓冲大小
	BOOL SetBufferSize(DWORD dInputBuff, DWORD dOutBuffer);
	//设置超时
	BOOL SetTimeouts(COMMTIMEOUTS &timeouts);

	//刷新缓冲区
	BOOL ReFreshBuff(DWORD flags);
	//刷新缓冲区
	BOOL ReFreshBuff();
	//写数据
	DWORD WriteData(char *pBuffer, int nLength);
	//读数据
	DWORD ReadData(char *pBuffer, int nLength);
	//写字符串
	DWORD WriteStr(std::string str);
	//关闭串口
	void CloseCOM();
	// 获取串口列表
	void GetComList_Reg();
	//判断串口是否打开s
	BOOL IsOpened();
	//得到最后一次失败的错误信息
	std::string GetSerialLastError();
	//线程函数
	UINT ThreadFunc();
	std::thread thread_1;
	//设置回调函数
	void SetCallBack(IMSGCBSERIAL* pCB);
	std::vector<std::string> GetAvailableSerial() { return AvailableCOM_list; };
	bool bStopThread;

private:
	//设置最后一次的错误信息
	void SetSerialLastError(std::string strErrorMsg);
	//清除最后一次的错误信息
	void ClearSerialLastError();
	// 启动线程
	void StartThread();
	// 停止线程
	void StopThread();
private:
	/* data */
	HANDLE m_hCom;
	std::string m_last_error;
	std::vector<std::string> AvailableCOM_list;//可用串口列表
	IMSGCBSERIAL* m_pCB;//回调函数指针
};
#endif