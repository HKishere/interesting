// OpenClientPropPage.cpp : COpenClientPropPage 属性页类的实现。

#include "stdafx.h"
#include "OpenClient.h"
#include "OpenClientPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COpenClientPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(COpenClientPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(COpenClientPropPage, "MFCACTIVEXCONT.OpenClientPropPage.1",
	0x9a36fde0,0x17a2,0x43ab,0xa4,0xbe,0x0a,0x05,0x3e,0x2e,0xa6,0xa0)

// COpenClientPropPage::COpenClientPropPageFactory::UpdateRegistry -
// 添加或移除 COpenClientPropPage 的系统注册表项

BOOL COpenClientPropPage::COpenClientPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OPENCLIENT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// COpenClientPropPage::COpenClientPropPage - 构造函数

COpenClientPropPage::COpenClientPropPage() :
	COlePropertyPage(IDD, IDS_OPENCLIENT_PPG_CAPTION)
{
}

// COpenClientPropPage::DoDataExchange - 在页和属性间移动数据

void COpenClientPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// COpenClientPropPage 消息处理程序
