#pragma once


// About 对话框

class About : public CDialogEx
{
	DECLARE_DYNAMIC(About)

public:
	afx_msg
	About(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~About();
	HWND aboutm_hWnd = this->m_hWnd;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
