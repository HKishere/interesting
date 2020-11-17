
// DatabaseUpdateDlg.cpp: 实现文件
//
#include <windows.h>
#include "stdafx.h"
#include "DatabaseUpdate.h"
#include "DatabaseUpdateDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDatabaseUpdateDlg 对话框



CDatabaseUpdateDlg::CDatabaseUpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATABASEUPDATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDatabaseUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, INIFilePath);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, UpdateFilePath);
	DDX_Control(pDX, IDC_BUTTON1, btn_Update);
	DDX_Control(pDX, IDC_PROGRESS1, ProgressBar);
}

BEGIN_MESSAGE_MAP(CDatabaseUpdateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CDatabaseUpdateDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDOK, &CDatabaseUpdateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDatabaseUpdateDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDatabaseUpdateDlg 消息处理程序

BOOL CDatabaseUpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	INIFilePath.SetWindowText(_T("./HF1.2B_Config.ini"));
	UpdateFilePath.SetWindowText(_T("./patch.txt"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDatabaseUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDatabaseUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDatabaseUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CDatabaseUpdateDlg::UpdateDatebase(CString inifilepath, CString updatefilepath)
{
	std::ifstream f_inifile;
	char buff[255];
	f_inifile.open(inifilepath);
	ProgressBar.SetPos(15);
	if (!f_inifile.is_open()) {
		CString str;
		str.Format(_T("配置打开失败失败"));
		MessageBox(str, NULL);
		f_inifile.close();
		return 0;
	}
	std::string host;
	std::string user;
	std::string password;
	std::string database;
	std::string port;
	while (f_inifile.getline(buff, 255)) {
		std::string line(buff);
		if (line.find("host") != -1) {
			host = line.substr(5, line.size());
		}
		if (line.find("user") != -1) {
			user = line.substr(5, line.size());
		}
		if (line.find("password") != -1) {
			password = line.substr(9, line.size());
		}
		if (line.find("database") != -1) {
			database = line.substr(9, line.size());
		}
		if (line.find("port") != -1) {
			port = line.substr(5, line.size());
		}
		if (host.size() > 0 && user.size() > 0 && password.size() > 0 && database.size() > 0 && port.size() > 0)
		{
			break;
		}
	}
	ProgressBar.SetPos(35);
	if (host.size() == 0 || user.size() == 0 || password.size() == 0 || database.size() == 0 || port.size() == 0)
	{
		CString str;
		ProgressBar.SetBarColor(RGB(0,0,0));
		str.Format(_T("配置信息缺失,检查ini文件"));
		MessageBox(str, NULL);
		f_inifile.close();
		return 0;
	}
	f_inifile.close();

	ProgressBar.SetPos(55);
	MYSQL conn;
	mysql_init(&conn);

	std::ifstream f_patched;
	if (!mysql_real_connect(&conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), stoi(port), NULL, 0)) {
		CString str;
		str.Format(_T("连接数据库失败",mysql_error(&conn)));
		f_patched.close();
		MessageBox(str, NULL);
		return 0;
	}
	else {
		f_patched.open(updatefilepath);
		if (!f_patched.is_open()) {
			CString str;
			ProgressBar.SetPos(65);
			str.Format(_T("读取更新文件失败"));
			f_patched.close();
			MessageBox(str, NULL);
			return 0;
		}
		int i = 1;
		ProgressBar.SetPos(75);
		while (f_patched.getline(buff, 255)){
			if (mysql_query(&conn, buff)) {//通过mysql_query函数执行SQL语句
				CString str;
				str.Format(_T("第 %d 条语句执行失败!!请检查SQL语句!"), i);
				f_patched.close();
				MessageBox(str, NULL);
				return 0;
			}
			else{
			}
			i++;
		}
	}
	ProgressBar.SetPos(100);
	MessageBox(_T("更新成功"), NULL);
	f_patched.close();
	mysql_close(&conn);
	return 1;
}



void CDatabaseUpdateDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDatabaseUpdateDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}



void CDatabaseUpdateDlg::OnBnClickedButton1()
{
	CString s_inifile;
	CString s_updatefile;
	INIFilePath.GetWindowText(s_inifile);
	UpdateFilePath.GetWindowText(s_updatefile);
	int ret = UpdateDatebase(s_inifile, s_updatefile);
	if (ret == 1)
	{
		ProgressBar.SetPos(100);
	}
	else
	{
		ProgressBar.SetPos(0);
	}
	// TODO: 在此添加控件通知处理程序代码
}
