
// MyGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PoisonedWine.h"
#include "PoisonedWineDlg.h"
#include "afxdialogex.h"
#include"About.h"
#include"Button.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyGameDlg::CMyGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CMyGameDlg 消息处理程序

BOOL CMyGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		// 获得屏幕分辨率
	int w = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	//设置窗口长宽
	int winwidth =1120;
	int winheight =630;
	// 窗口位置
	{
		// 设置本窗口大小, 屏幕居中
		MoveWindow(w/2-winwidth/2,y/2-winheight/2, winwidth,winheight);
	}

	//初始化 游戏对象 : 向本窗口绘图
	m_pGame = std::make_shared<CGame>(GetSafeHwnd(), 0.0f, 0.0f, float(w), float(y));
	std::shared_ptr<Button> button = std::make_shared<Button>();
	// 启动定时器，游戏帧
	SetTimer(1,20, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyGameDlg::OnPaint()
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
HCURSOR CMyGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMyGameDlg::PreTranslateMessage(MSG* pMsg)
{
	return CDialogEx::PreTranslateMessage(pMsg);
}

void  CMyGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pGame->OnLButtonDown(nFlags, point); 		
	CDialogEx::OnLButtonDown(nFlags, point);
}


void  CMyGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_pGame->OnLButtonUp(nFlags, point); 		
	CDialogEx::OnLButtonUp(nFlags, point);
}

void  CMyGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pGame->OnMouseMove(nFlags, point); 			// 转发鼠标消息
	CDialogEx::OnMouseMove(nFlags, point);
}

void  CMyGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_pGame->EnterFrame(0); 						// 进入游戏帧
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CMyGameDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pGame->mouseStyle == NULL)
		return CMyGameDlg::OnSetCursor(pWnd, nHitTest, message);
	::SetCursor(m_pGame->mouseStyle);
	return TRUE;
}


void CMyGameDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnLButtonDblClk(nFlags, point);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
