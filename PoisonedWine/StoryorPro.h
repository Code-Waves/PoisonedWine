#pragma once
#include"Button.h"
class StoryorPro :public Button
{
public:
	StoryorPro(HWND hWnd);
	~StoryorPro();
	HWND m_hWnd;
	CRect m_rcClient;// 客户区的大小
	bool isstory = false;
	bool isprogram = false;
	void Draw(bool& inaboutico, bool& inproico, int& gamestate, Gdiplus::Graphics& gh);
	std::vector<Image*>storyorpro;
	Gdiplus::Image* gsbjimg = Image::FromFile(_T(".\\pic\\故事背景.gif"));//故事背景
	Gdiplus::Image* sfysimg = Image::FromFile(_T(".\\pic\\算法演示.gif"));//算法演示
};

