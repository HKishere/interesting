#pragma once

// OpenClientPropPage.h: COpenClientPropPage 属性页类的声明。


// COpenClientPropPage : 请参阅 OpenClientPropPage.cpp 了解实现。

class COpenClientPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(COpenClientPropPage)
	DECLARE_OLECREATE_EX(COpenClientPropPage)

// 构造函数
public:
	COpenClientPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_OPENCLIENT };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

