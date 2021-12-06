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
	//�򿪴���,������
	BOOL OpenCOM(const char* strSerialName, DWORD cBaudRate, BYTE cParity, unsigned char cByteSize, unsigned char cStopBits);

	//���û����С
	BOOL SetBufferSize(DWORD dInputBuff, DWORD dOutBuffer);
	//���ó�ʱ
	BOOL SetTimeouts(COMMTIMEOUTS &timeouts);

	//ˢ�»�����
	BOOL ReFreshBuff(DWORD flags);
	//ˢ�»�����
	BOOL ReFreshBuff();
	//д����
	DWORD WriteData(char *pBuffer, int nLength);
	//������
	DWORD ReadData(char *pBuffer, int nLength);
	//д�ַ���
	DWORD WriteStr(std::string str);
	//�رմ���
	void CloseCOM();
	// ��ȡ�����б�
	void GetComList_Reg();
	//�жϴ����Ƿ��s
	BOOL IsOpened();
	//�õ����һ��ʧ�ܵĴ�����Ϣ
	std::string GetSerialLastError();
	//�̺߳���
	UINT ThreadFunc();
	std::thread thread_1;
	//���ûص�����
	void SetCallBack(IMSGCBSERIAL* pCB);
	std::vector<std::string> GetAvailableSerial() { return AvailableCOM_list; };
	bool bStopThread;

private:
	//�������һ�εĴ�����Ϣ
	void SetSerialLastError(std::string strErrorMsg);
	//������һ�εĴ�����Ϣ
	void ClearSerialLastError();
	// �����߳�
	void StartThread();
	// ֹͣ�߳�
	void StopThread();
private:
	/* data */
	HANDLE m_hCom;
	std::string m_last_error;
	std::vector<std::string> AvailableCOM_list;//���ô����б�
	IMSGCBSERIAL* m_pCB;//�ص�����ָ��
};
#endif