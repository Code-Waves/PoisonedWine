#pragma once
#include"Button.h"
class  OtherFuction :public Button
{
public:
	OtherFuction(HWND hWnd);
	~OtherFuction();
	HWND m_hWnd;
	CRect m_rcClient;// �ͻ����Ĵ�С
	bool fire = false;//����
	bool functionon = false;
	int rockheight = 0;//��������߶�
	bool otherfunction = true;//������������ ���λ�� RGB ��ͼ FPS 
	CString rackmusicpath;//��䷢������
	Gdiplus::Image* rackstarimg = Image::FromFile(_T(".\\pic\\rockstar1.gif")); // �������
    //Gdiplus::Image* rackflyimg = Image::FromFile(_T(".\\pic\\rockfly.png")); // �������
	Gdiplus::Image* rockbottomimg = Image::FromFile(_T(".\\pic\\bottom.gif")); // ������
	Gdiplus::Image* otherimg = Image::FromFile(_T(".\\pic\\otherimg.gif")); // ���������ؿ�ʼͼ��
	void Start(bool& inico, int& gamestate, Gdiplus::Graphics& gh);
};
