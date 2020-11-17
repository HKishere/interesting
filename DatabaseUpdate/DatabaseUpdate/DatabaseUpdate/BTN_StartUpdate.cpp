// BTN_StartUpdate.cpp: 实现文件
//

#include "stdafx.h"
#include "DatabaseUpdate.h"
#include "BTN_StartUpdate.h"
#include "afxdialogex.h"


// BTN_StartUpdate 对话框

IMPLEMENT_DYNAMIC(BTN_StartUpdate, CDialogEx)

BTN_StartUpdate::BTN_StartUpdate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATABASEUPDATE_DIALOG, pParent)
{

}

BTN_StartUpdate::~BTN_StartUpdate()
{
}

void BTN_StartUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BTN_StartUpdate, CDialogEx)
END_MESSAGE_MAP()


// BTN_StartUpdate 消息处理程序
