#pragma once
#include"Button.h"
class AboutFunction:public Button
{
public:
		AboutFunction(HWND hWnd);
		~AboutFunction();
		HWND m_hWnd;
		CRect m_rcClient;// 客户区的大小
		Gdiplus::Image* aboutimg = Image::FromFile(_T(".\\pic\\about.gif"));//about小灯泡
		Gdiplus::Image* application = Image::FromFile(_T(".\\pic\\application.png"));
		Gdiplus::Image* round = Image::FromFile(_T(".\\pic\\u11.png"));
		void Draw(bool& inico,int &gamestate,Gdiplus::Graphics& gh);
		void Drawbackground(Gdiplus::Graphics& gh);
};

