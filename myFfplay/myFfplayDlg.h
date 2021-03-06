
// myFfplayDlg.h : 头文件
//


//#include <msclr/marshal.h>
//using namespace msclr::interop;

#pragma once

//HINSTANCE hPro=LoadLibrary(LPCWSTR("PTZControl.dll")); 
	//#using <mscorlib.dll>
#include <afxdb.h>

 class CmyFfplayDlg : public CDialogEx
{
// 构造
public:
	CmyFfplayDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYFFPLAY_DIALOG };
	enum PTZ_SET{ 
		YUNTAI_TURN_NULL,
		YUNTAI_TURN_UP=1,
		YUNTAI_TURN_DOWN=-1,
		YUNTAI_TURN_LEFT=-1,
		YUNTAI_TURN_RIGHT=1,
		CAMERA_ZOOM_NEAR=1,
		CAMERA_ZOOM_AWAY=-1,
		CAMERA_FOCUS_NEAR=1,
		CAMERA_FOCUS_AWAY=-1,
		WIPER_SET_ON=0,
		WIPER_SET_OFF=1,
		LEN_SET_ON=0,
		LEN_SET_OFF=1,
		HEATE_SET_ON=0,
		HEATE_SET_OFF=1,
		APERTURE_SELECT_UP=1,
		APERTURE_SELECT_DOWN=-1,
		AUTOAPERTURE_ON=0,
		AUTOAPERTURE_OFF=1
	};
	CDatabase base1;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	gcroot<PTZControl::PTZControl^> pcontrol;//这个是用方法要注意，解决托管代码不能定义全局变量以及静态变量问题
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CButtonST m_btn; 
	//CBitmapButton m_button;
	// 服务器端IP
	CString m_ServerIp;
	int m_ServerPort;
	CString m_ClientIp;
	int m_ClientPort;
	int m_CamType;
	int m_CamPort;
	int m_YtSpeed;	
	int m_OldPan;
	int m_NewPan;
	int m_OldTilt;
	int m_NewTilt;
	int m_OldZoom;
	int m_NewZoom;
	int m_OldFocus;
	int m_NewFocus;
	int m_MSecond;
	int m_Gain;
	int m_Shutter;
	int m_FilterNd;	
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedBreak();
	afx_msg void OnBnClickedYtUp();
	afx_msg void OnBnClickedYtLeft();
	afx_msg void OnBnClickedYtRight();
	afx_msg void OnBnClickedYtDown();
	afx_msg void OnBnClickedYtStop();

	afx_msg void OnBnClickedZoomAway();
	afx_msg void OnBnClickedZoomNear();
	afx_msg void OnBnClickedFocusAway();
	afx_msg void OnBnClickedFocusNear();

	afx_msg void OnBnClickedPtzTraceBt();
	afx_msg void OnBnClickedWiperOnBt();
	afx_msg void OnBnClickedWiperOffBt();
	afx_msg void OnBnClickedLenOnBt();
	afx_msg void OnBnClickedLenOffBt();
	afx_msg void OnBnClickedHeateOnBt();
	afx_msg void OnBnClickedHeateOffBt();
	afx_msg void OnBnClickedPanAngleBt();
	afx_msg void OnBnClickedTiltAngleBt();
	afx_msg void OnBnClickedCameraAbbBt();
	afx_msg void OnBnClickedCameraAwbBt();
	afx_msg void OnBnClickedApertureUpBt();
	afx_msg void OnBnClickedApertureDownBt();
	afx_msg void OnBnClickedAutoaperOnBt();
	afx_msg void OnBnClickedAutoaperOffBt();
	afx_msg void OnBnClickedMasterBt();
	afx_msg void OnBnClickedShutterBt();
	afx_msg void OnBnClickedFilterNdBt();
	afx_msg void OnBnClickedMasterGBt();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedYtLuBt();
	afx_msg void OnBnClickedYtRuBt();
	afx_msg void OnBnClickedYtLdBt();
	afx_msg void OnBnClickedYtRdBt();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton4();
};
