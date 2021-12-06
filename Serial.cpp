#include "Serial.h"
#include <windows.h>
#include <string>
#include <atlbase.h>
#include <atlconv.h>

SerialCtl::SerialCtl()
{
	m_hCom = NULL;
	m_last_error = "";
}
SerialCtl::~SerialCtl()
{

}
BOOL SerialCtl::OpenCOM(const char* strSerialName, DWORD cBaudRate, BYTE cParity, unsigned char cByteSize, unsigned char cStopBits)
{
	// 打开串口
	USES_CONVERSION;
	m_hCom = CreateFile(A2T(strSerialName),
		GENERIC_READ | GENERIC_WRITE, //允许读和写
		0,  //独占方式
		NULL,
		OPEN_EXISTING,  //打开而不是创建
		FILE_ATTRIBUTE_NORMAL, //重叠方式 这里指定同步方式, 需要异步的话填FILE_FLAG_OVERLAPPED, 
								//且要和后面writefile中的最后一个参数对应, 同步时填NULL, 异步时需要使用OVERLAPPED结构体
		NULL);
	int ret = GetLastError();
	if (INVALID_HANDLE_VALUE == m_hCom)//出错判断
	{
		m_hCom = NULL;
		SetSerialLastError("串口创建失败!");
		GetComList_Reg();
		if (AvailableCOM_list.size() > 0)
		{
			for (int i = 0; i < (int)AvailableCOM_list.size(); i++)
			{
				printf("可用串口: %s", AvailableCOM_list[i]);
			}
		}
		else
		{
			printf("无可用串口");
		}
		return false;
	}

	//配置串口信息
	DCB COMInfo;
	if (!GetCommState(m_hCom, &COMInfo))
	{
		return false;
	}
	COMInfo.DCBlength = sizeof(DCB);
	COMInfo.BaudRate = cBaudRate;
	COMInfo.Parity = cParity;
	COMInfo.ByteSize = cByteSize;
	COMInfo.StopBits = cStopBits;

	if (false == SetCommState(m_hCom, &COMInfo))//配置串行端口信息
	{
		SetSerialLastError("串口打开失败 : 串口信息配置失败!");
		return false;
	}

	//超时处理
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = 0; //读间隔超时
	// 把间隔超时设为最大，把总超时设为0将导致ReadFile立即返回并完成操作 
	timeouts.ReadTotalTimeoutMultiplier = 0; //读时间系数
	timeouts.ReadTotalTimeoutConstant = 200; //读时间常量
	timeouts.WriteTotalTimeoutMultiplier = 5; // 写时间系数
	timeouts.WriteTotalTimeoutConstant = 500; //写时间常量

	if (false == SetCommTimeouts(m_hCom, &timeouts))
	{
		SetSerialLastError("串口打开失败 : 串口打开超时");
		return false;
	}
	if (SetBufferSize(1024, 1024))
	{
		SetSerialLastError("串口打开失败 : 串口缓冲区大小设置失败");
		return false;
	}


	//停止串口读写, 清空缓冲区
	if (false == PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT))
	{
		SetSerialLastError("串口打开失败 : 串口缓冲区重置失败");
		return FALSE;
	}
	StartThread();
	return TRUE;
}

BOOL SerialCtl::SetBufferSize(DWORD dInputBuff, DWORD dOutBuffer)
{
	if (SetupComm(m_hCom, dInputBuff, dOutBuffer))
	{
		SetSerialLastError("串口缓冲区设置失败");
		return FALSE;
	}
	return TRUE;
}


DWORD SerialCtl::WriteData(char *pBuffer, int nLength)
{
	DWORD dWriteSize = 0;
	BOOL ret = WriteFile(m_hCom, pBuffer, nLength, &dWriteSize, NULL);

	if (!ret)
	{
		return 0;
	}
	return dWriteSize;
}

DWORD SerialCtl::ReadData(char *pBuffer, int nLength)
{
	DWORD dWriteSize = 0;
	BOOL ret = ReadFile(m_hCom, pBuffer, nLength, &dWriteSize, NULL);

	if (!ret)
	{
		return 0;
	}
	return dWriteSize;
}

BOOL SerialCtl::IsOpened()
{
	if (m_hCom == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

UINT SerialCtl::ThreadFunc()
{
	char bBuff[2048] = { 0 };
	while (!bStopThread)
	{
		DWORD dRecvNum = ReadData(bBuff, 1024);
		if (dRecvNum)
		{
			if (m_pCB)
			{
				m_pCB->OnRecvDataSerial(bBuff, 100);
			}
			memset(bBuff, 0, 1024);
		}
		else
		{
			Sleep(10);
		}
	}
	return 0;

}

void SerialCtl::SetCallBack(IMSGCBSERIAL* pCB)
{
	m_pCB = pCB;
}

void SerialCtl::SetSerialLastError(std::string strErrorMsg)
{
	printf(strErrorMsg.c_str());
	m_last_error = strErrorMsg;
}

void SerialCtl::ClearSerialLastError()
{
	m_last_error = "";
}

void SerialCtl::StartThread()
{
	bStopThread = FALSE;
	std::thread thread_1(&SerialCtl::ThreadFunc, this);
	thread_1.detach();
}

void SerialCtl::StopThread()
{
	bStopThread = TRUE;
}

void SerialCtl::CloseCOM()
{
	if (NULL == m_hCom)
		return;
	CloseHandle(m_hCom);
	StopThread();
	m_hCom = NULL;
}

void SerialCtl::GetComList_Reg()
{
	AvailableCOM_list.clear();
	HKEY hkey;
	int result;
	int i = 0;

	// 打开串口注册表   
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("Hardware\\DeviceMap\\SerialComm"),
		NULL,
		KEY_READ,
		&hkey);

	if (ERROR_SUCCESS == result)
	{
		TCHAR PortName[0x100], CommName[0x100];
		DWORD dwLong, dwSize;
		do
		{
			dwSize = sizeof(PortName) / sizeof(TCHAR);
			dwLong = dwSize;
			result = RegEnumValue(hkey, i, PortName, &dwLong, NULL, NULL, (LPBYTE)CommName, &dwSize);
			if (ERROR_NO_MORE_ITEMS == result)
			{
				break;
			}
			USES_CONVERSION;
			std::string temp_str(T2A(CommName), strlen(T2A(CommName)));
			AvailableCOM_list.push_back(temp_str);   // CommName就是串口名字"COM4"
			i++;
		} while (1);

		RegCloseKey(hkey);
	}
}