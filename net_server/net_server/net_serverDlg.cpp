
// net_serverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "net_server.h"
#include "net_serverDlg.h"
#include "afxdialogex.h"
#include "socket.h"
#include "cat_name.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cnet_serverDlg 对话框




Cnet_serverDlg::Cnet_serverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cnet_serverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cnet_serverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, chat_1);
	DDX_Control(pDX, IDC_EDIT3, chat_2);
	DDX_Control(pDX, IDC_EDIT2, chat_3);
	DDX_Control(pDX, IDC_EDIT4, chat_4);
}

BEGIN_MESSAGE_MAP(Cnet_serverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cnet_serverDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &Cnet_serverDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &Cnet_serverDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &Cnet_serverDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Cnet_serverDlg 消息处理程序

BOOL Cnet_serverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cnet_serverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cnet_serverDlg::OnPaint()
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
HCURSOR Cnet_serverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cnet_serverDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString data;

	Cnet_serverDlg *dlg = this;

	chat_2.GetWindowTextA(data);
	const char* cstr = data.GetString();
	chat_4.GetWindowTextA(data);
	int portValue = _ttoi(data);

	creat_chat_room(dlg, cstr, portValue);
}


void Cnet_serverDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	close_socket();
	MessageBox(_T("退出监听!"));
}


void Cnet_serverDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	cat_name cat_t;
	INT_PTR result = cat_t.DoModal();

	if (result == IDOK)
	{
		// 用户点击了"OK"按钮
		// 在这里执行相关的操作
		// ...
		Cnet_serverDlg* dlg = this;
		SentUserInfo(dlg);
	}
}

void Cnet_serverDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
