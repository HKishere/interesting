
// DatabaseUpdateDlg.h: 头文件
//

#pragma once


// CDatabaseUpdateDlg 对话框
class CDatabaseUpdateDlg : public CDialogEx
{
// 构造
public:
	CDatabaseUpdateDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATABASEUPDATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	int UpdateDatebase(CString inifilepath, CString updatefilepath);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedOk();
	CMFCEditBrowseCtrl INIFilePath;
	CMFCEditBrowseCtrl UpdateFilePath;
	CButton btn_Update;
	afx_msg void OnBnClickedButton1();
	CProgressCtrl ProgressBar;
};
