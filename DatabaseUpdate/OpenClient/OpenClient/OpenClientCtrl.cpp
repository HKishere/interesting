// OpenClientCtrl.cpp : COpenClientCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "OpenClient.h"
#include "OpenClientCtrl.h"
#include "OpenClientPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COpenClientCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(COpenClientCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(COpenClientCtrl, COleControl)
	DISP_FUNCTION_ID(COpenClientCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(COpenClientCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(COpenClientCtrl, 1)
	PROPPAGEID(COpenClientPropPage::guid)
END_PROPPAGEIDS(COpenClientCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(COpenClientCtrl, "MFCACTIVEXCONTRO.OpenClientCtrl.1",
	0x1c40c893,0x4ad4,0x48af,0x9f,0x35,0x87,0x86,0x7b,0x48,0x6e,0x31)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(COpenClientCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DOpenClient = {0x7259c739,0xa75e,0x4d3a,{0xae,0x4b,0xec,0x81,0x5b,0xe8,0x24,0xda}};
const IID IID_DOpenClientEvents = {0x47267c73,0xe3bc,0x43fb,{0xac,0xe8,0xb9,0x16,0x87,0xcb,0x98,0x4b}};

// 控件类型信息

static const DWORD _dwOpenClientOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(COpenClientCtrl, IDS_OPENCLIENT, _dwOpenClientOleMisc)

// COpenClientCtrl::COpenClientCtrlFactory::UpdateRegistry -
// 添加或移除 COpenClientCtrl 的系统注册表项

BOOL COpenClientCtrl::COpenClientCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_OPENCLIENT,
			IDB_OPENCLIENT,
			afxRegApartmentThreading,
			_dwOpenClientOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// COpenClientCtrl::COpenClientCtrl - 构造函数

COpenClientCtrl::COpenClientCtrl()
{
	InitializeIIDs(&IID_DOpenClient, &IID_DOpenClientEvents);
	// TODO:  在此初始化控件的实例数据。
}

// COpenClientCtrl::~COpenClientCtrl - 析构函数

COpenClientCtrl::~COpenClientCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// COpenClientCtrl::OnDraw - 绘图函数

void COpenClientCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// COpenClientCtrl::DoPropExchange - 持久性支持

void COpenClientCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// COpenClientCtrl::OnResetState - 将控件重置为默认状态

void COpenClientCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// COpenClientCtrl::AboutBox - 向用户显示“关于”框

void COpenClientCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_OPENCLIENT);
	dlgAbout.DoModal();
}


// COpenClientCtrl 消息处理程序
int COpenClientCtrl::OpenMainFrame()
{
	system("D:\GIT\interesting\onekey.bat");
	return 1
}

