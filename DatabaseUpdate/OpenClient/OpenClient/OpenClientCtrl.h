#pragma once

// OpenClientCtrl.h : COpenClientCtrl ActiveX 控件类的声明。


// COpenClientCtrl : 请参阅 OpenClientCtrl.cpp 了解实现。

class COpenClientCtrl : public COleControl
{
	DECLARE_DYNCREATE(COpenClientCtrl)

// 构造函数
public:
	COpenClientCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~COpenClientCtrl();

	DECLARE_OLECREATE_EX(COpenClientCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(COpenClientCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(COpenClientCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(COpenClientCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();
	afx_msg int OpenMainFrame();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
	};
};

