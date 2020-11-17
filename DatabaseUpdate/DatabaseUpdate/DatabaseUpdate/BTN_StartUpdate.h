#pragma once


// BTN_StartUpdate 对话框

class BTN_StartUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(BTN_StartUpdate)

public:
	BTN_StartUpdate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BTN_StartUpdate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATABASEUPDATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
