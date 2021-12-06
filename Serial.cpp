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
	// �򿪴���
	USES_CONVERSION;
	m_hCom = CreateFile(A2T(strSerialName),
		GENERIC_READ | GENERIC_WRITE, //�������д
		0,  //��ռ��ʽ
		NULL,
		OPEN_EXISTING,  //�򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL, //�ص���ʽ ����ָ��ͬ����ʽ, ��Ҫ�첽�Ļ���FILE_FLAG_OVERLAPPED, 
								//��Ҫ�ͺ���writefile�е����һ��������Ӧ, ͬ��ʱ��NULL, �첽ʱ��Ҫʹ��OVERLAPPED�ṹ��
		NULL);
	int ret = GetLastError();
	if (INVALID_HANDLE_VALUE == m_hCom)//�����ж�
	{
		m_hCom = NULL;
		SetSerialLastError("���ڴ���ʧ��!");
		GetComList_Reg();
		if (AvailableCOM_list.size() > 0)
		{
			for (int i = 0; i < (int)AvailableCOM_list.size(); i++)
			{
				printf("���ô���: %s", AvailableCOM_list[i]);
			}
		}
		else
		{
			printf("�޿��ô���");
		}
		return false;
	}

	//���ô�����Ϣ
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

	if (false == SetCommState(m_hCom, &COMInfo))//���ô��ж˿���Ϣ
	{
		SetSerialLastError("���ڴ�ʧ�� : ������Ϣ����ʧ��!");
		return false;
	}

	//��ʱ����
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = 0; //�������ʱ
	// �Ѽ����ʱ��Ϊ��󣬰��ܳ�ʱ��Ϊ0������ReadFile�������ز���ɲ��� 
	timeouts.ReadTotalTimeoutMultiplier = 0; //��ʱ��ϵ��
	timeouts.ReadTotalTimeoutConstant = 200; //��ʱ�䳣��
	timeouts.WriteTotalTimeoutMultiplier = 5; // дʱ��ϵ��
	timeouts.WriteTotalTimeoutConstant = 500; //дʱ�䳣��

	if (false == SetCommTimeouts(m_hCom, &timeouts))
	{
		SetSerialLastError("���ڴ�ʧ�� : ���ڴ򿪳�ʱ");
		return false;
	}
	if (SetBufferSize(1024, 1024))
	{
		SetSerialLastError("���ڴ�ʧ�� : ���ڻ�������С����ʧ��");
		return false;
	}


	//ֹͣ���ڶ�д, ��ջ�����
	if (false == PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT))
	{
		SetSerialLastError("���ڴ�ʧ�� : ���ڻ���������ʧ��");
		return FALSE;
	}
	StartThread();
	return TRUE;
}

BOOL SerialCtl::SetBufferSize(DWORD dInputBuff, DWORD dOutBuffer)
{
	if (SetupComm(m_hCom, dInputBuff, dOutBuffer))
	{
		SetSerialLastError("���ڻ���������ʧ��");
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

	// �򿪴���ע���   
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
			AvailableCOM_list.push_back(temp_str);   // CommName���Ǵ�������"COM4"
			i++;
		} while (1);

		RegCloseKey(hkey);
	}
}