#pragma once
#include"Button.h"
class  OtherFuction :public Button
{
public:
	OtherFuction(HWND hWnd);
	~OtherFuction();
	HWND m_hWnd;
	CRect m_rcClient;// 客户区的大小
	bool fire = false;//发射
	bool functionon = false;
	int rockheight = 0;//火箭上升高度
	bool otherfunction = true;//开启其他功能 鼠标位置 RGB 截图 FPS 
	CString rackmusicpath;//火间发射声音
	Gdiplus::Image* rackstarimg = Image::FromFile(_T(".\\pic\\rockstar1.gif")); // 火箭启动
    //Gdiplus::Image* rackflyimg = Image::FromFile(_T(".\\pic\\rockfly.png")); // 火箭飞行
	Gdiplus::Image* rockbottomimg = Image::FromFile(_T(".\\pic\\bottom.gif")); // 火间底座
	Gdiplus::Image* otherimg = Image::FromFile(_T(".\\pic\\otherimg.gif")); // 其他功能呢开始图标
	void Start(bool& inico, int& gamestate, Gdiplus::Graphics& gh);
};
