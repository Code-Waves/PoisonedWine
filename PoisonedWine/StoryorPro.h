#pragma once
#include"Button.h"
class StoryorPro :public Button
{
public:
	StoryorPro(HWND hWnd);
	~StoryorPro();
	HWND m_hWnd;
	CRect m_rcClient;// �ͻ����Ĵ�С
	bool isstory = false;
	bool isprogram = false;
	void Draw(bool& inaboutico, bool& inproico, int& gamestate, Gdiplus::Graphics& gh);
	std::vector<Image*>storyorpro;
	Gdiplus::Image* gsbjimg = Image::FromFile(_T(".\\pic\\���±���.gif"));//���±���
	Gdiplus::Image* sfysimg = Image::FromFile(_T(".\\pic\\�㷨��ʾ.gif"));//�㷨��ʾ
};

