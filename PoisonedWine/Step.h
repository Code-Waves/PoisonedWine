#pragma once
#include "pch.h"
#include "Numberarr.h"
class Step :public Button
{
public:
	int step = 1;
	PointF origin{ 0,0 };
	PointF origin1{ 650,100 };
	Step(HWND hWnd);
	void toZero();//归零计算进制之前   先归零
	void toBinary(int sum);
	bool bofang = true;
	CRect m_rcClient;
	int su =3;

	int hei = 0;//最后上升

	int index1 = 0, index2 = 0, index3 = 0;
	ULONGLONG time1 = ::GetTickCount64(), time2 = ::GetTickCount64(), time3 = ::GetTickCount64(), time4 = ::GetTickCount64();
	Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\background3.gif"));
	Gdiplus::Image* backgroundimg4 = Image::FromFile(_T(".\\pic\\background4.gif"));
	Gdiplus::Image* backgroundimg5 = Image::FromFile(_T(".\\pic\\background5.gif"));
	Gdiplus::Image* lbnzimg = Image::FromFile(_T(".\\pic\\lbnz.gif"));
	Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome.gif"));
	Gdiplus::Image* tiaoguoimg = Image::FromFile(_T(".\\pic\\跳过.gif"));
	Gdiplus::Image* jiuimg = Image::FromFile(_T(".\\pic\\酒桶编号.gif"));
	Gdiplus::Image* img0999 = Image::FromFile(_T(".\\pic\\0999.gif"));
	Gdiplus::Image* img110 = Image::FromFile(_T(".\\pic\\1-10.gif"));

	CRect backhomerect;//主菜单
	CPoint backhomecen;
	CRect tiaoguorect;//跳过
	CPoint tiaoguocen;
	std::vector<Image*>timeimg;//0-9
	int bi[10] = { 0 };

	int shi = 0, ge = 0;
	std::vector<BandMan*>bandmans;//奴隶10个
	std::vector<Numberarr*>numarr;//0-9////数字集合


	void init();

	void Choose(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);
	void characterinit();
	void Draw(bool& inico1, bool& inico2, int& gamestate,Gdiplus::Graphics& gh);
	void Firststep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);
	double Theta(CPoint T, CPoint V);
	void Secondstep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);
	void Endstep(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);

	void Progra(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);
};



