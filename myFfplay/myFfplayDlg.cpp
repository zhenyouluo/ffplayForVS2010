
// myFfplayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "myFfplay.h"
#include "myFfplayDlg.h"
#include "afxdialogex.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "myHead.h"
#include "SDL\SDL.h"
#include "SDL\SDL_thread.h"
#ifdef __cplusplus
};
#endif 
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


// CmyFfplayDlg 对话框



CmyFfplayDlg::CmyFfplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyFfplayDlg::IDD, pParent)
	, m_ServerIp(_T(""))
	, m_ServerPort(0)
	, m_ClientIp(_T(""))
	, m_ClientPort(0)
	, m_CamType(0)
	, m_CamPort(0)
	, m_YtSpeed(0)
	, m_OldPan(0)
	, m_NewPan(0)
	, m_OldTilt(0)
	, m_NewTilt(0)
	, m_OldZoom(0)
	, m_NewZoom(0)
	, m_OldFocus(0)
	, m_NewFocus(0)
	, m_MSecond(0)
	, m_Shutter(0)
	, m_FilterNd(0)
	, m_Gain(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pcontrol=gcnew PTZControl::PTZControl();

}

void CmyFfplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CmyFfplayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_CLOSE()

	ON_WM_SHOWWINDOW()
//	ON_WM_CREATE()
ON_WM_CREATE()
ON_BN_CLICKED(IDC_BUTTON1, &CmyFfplayDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CmyFfplayDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CmyFfplayDlg 消息处理程序

BOOL CmyFfplayDlg::OnInitDialog()
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

void CmyFfplayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmyFfplayDlg::OnPaint()
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
HCURSOR CmyFfplayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//extern void outptt();
//extern int main_ffplay();
extern int ffplay(char *argc, char **argv);

void CmyFfplayDlg::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知?理程序代?
#ifdef VIDEO_PICTURE_SIZE_AUTO
	CRect rc;
	char sdl_var[128]; 
	int picControl_w,picControl_h;
	HWND m_wnd=GetDlgItem(IDC_STATIC_VIDEO)->m_hWnd;
	GetDlgItem(IDC_STATIC_VIDEO)->GetClientRect(&rc);
	picControl_w=rc.Width();
	picControl_h=rc.Height();
	sprintf(sdl_var, "SDL_WINDOWID=0x%lx", m_wnd );//ﾖｰｿﾚｾ莖・
	ffplay(sdl_var, NULL,picControl_w,picControl_h);
#else
	sprintf(sdl_var, "SDL_WINDOWID=0x%lx", m_wnd );//ﾖｰｿﾚｾ莖・
	ffplay(sdl_var, NULL);

#endif

}

extern int main_ffplay();
void CmyFfplayDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知?理程序代?
	//ffplay(1, NULL);
#ifdef SET_MFC_WINDOW
		//CRect rc;
	char sdl_var[128]; 
	//int picControl_w,picControl_h;
	HWND m_wnd=GetDlgItem(IDC_STATIC_VIDEO)->m_hWnd;
	//GetDlgItem(IDC_STATIC_VIDEO)->GetClientRect(&rc);
	//picControl_w=rc.Width();
	//picControl_h=rc.Height();
	sprintf(sdl_var, "SDL_WINDOWID=0x%lx", m_wnd );//ﾖｰｿﾚｾ莖・
main_ffplay(sdl_var, NULL);
#else
	main_ffplay();
#endif
}


void CmyFfplayDlg::OnClose()
{
	// TODO: 在此添加消息?理程序代?和/或?用默??

	//MessageBox(_T("quit!"));
	CDialogEx::OnClose();
}




void CmyFfplayDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此?添加消息?理程序代?
	
}



int CmyFfplayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加??用的?建代?

	return 0;
}
#include <string>
using namespace std;


#include <shellapi.h>
void CmyFfplayDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知?理程序代?

	//ShellExecute(NULL,_T("open"),_T("cmd.exe"),_T("/c C:\\gifMake\\ffmpeg.exe -i rtmp://s2pchzxmtymn2k.cloudfront.net/cfx/st/mp4:sintel.mp4 -f image2  -r 1 -t 10 -s 220*220 C:\\gifMake\\i%d.jpeg & C:\\gifMake\\convert.exe  -delay 100 C:\\gifMake\\i1.jpeg C:\\gifMake\\i2.jpeg C:\\gifMake\\i3.jpeg C:\\gifMake\\i4.jpeg C:\\gifMake\\i5.jpeg C:\\gifMake\\i6.jpeg C:\\gifMake\\i7.jpeg C:\\gifMake\\i8.jpeg -loop 5  C:\\gifMake\\i.gif & del C:\\gifMake\\*.jpeg"),NULL,SW_HIDE); 
	system("C:\\gifMake\\ffmpeg.exe -i rtmp://s2pchzxmtymn2k.cloudfront.net/cfx/st/mp4:sintel.mp4 -f image2  -r 1 -t 10 -s 220*220 C:\\gifMake\\i%d.jpeg & C:\\gifMake\\convert.exe  -delay 100 C:\\gifMake\\i1.jpeg C:\\gifMake\\i2.jpeg C:\\gifMake\\i3.jpeg C:\\gifMake\\i4.jpeg C:\\gifMake\\i5.jpeg C:\\gifMake\\i6.jpeg C:\\gifMake\\i7.jpeg C:\\gifMake\\i8.jpeg -loop 5  C:\\gifMake\\i.gif & del C:\\gifMake\\*.jpeg");
}