// About.cpp: 实现文件
//

#include "pch.h"
#include "PoisonedWine.h"
#include "About.h"
#include "afxdialogex.h"


// About 对话框

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUT, pParent)
{
	
}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CRect rc;
	GetWindowRect(&rc); //获取窗口矩形（大小）//对应点的集合
	CPoint ptVertex[16] = {
		 { 70,0 },{90,20},{120,20},{120,50},{140,70},{120,90},{120,120},{90,120},
		 {70,140},{50,120},{20,120},{20,90},{0,70},{20,50},{20,20},{50,20}
	};
	for (int i = 0; i < 16; i++)
	{
		ptVertex[i].x *= 4.4;
		ptVertex[i].y *= 4.4;
		ptVertex[i].y += 40;
		ptVertex[i].x += 10;
	}

	CRgn m_rgn;   //定义窗口显示区域
	m_rgn.CreatePolygonRgn(ptVertex, 16, ALTERNATE);//根据顶点数组创建窗口的显示区域

	SetWindowRgn(m_rgn, TRUE);//添加到当前窗口

	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(About, CDialogEx)
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// About 消息处理程序


void About::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}

void About::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnCancel();
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void About::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

}
