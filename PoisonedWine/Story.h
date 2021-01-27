#pragma once
#include"Button.h"
class Story :public Button
{
public:
	Story(HWND hWnd);
	~Story();
	HWND m_hWnd;
	bool music = true;
	bool backhome = false;
	PointF origin{ 280.0f,0.0f };
	int wordindex = 0;
	SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
	Gdiplus::Font m_font{ L"楷体",13.0,CFE_BOLD };    // 输出文字字体
	CRect m_rcClient;// 客户区的大小
	Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome0.gif"));
	Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\background1.gif"));
	void Draw(bool& inico, std::vector<BandMan*>bandmans, Gdiplus::Graphics& gh);
};

