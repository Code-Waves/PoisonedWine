#pragma once
#include "pch.h"
#include "Numberarr.h"
#include <fstream>
#include<iostream>
#include <ctime>

class Start :public Button
{
public:
	int step = 1;
	Start(HWND hWnd);
	void toZero();//归零计算进制之前   先归零
	void toBinary(int sum);
	bool biu = true;
	bool biuend = true;
	bool bofang = true;
	CRect m_rcClient;
	int jian = 200;
	int kingp = 0;
	int hei = 0;

	bool addbandman = true;
	int bandaddindex = 0;
	bool prebo = true;

	ULONGLONG time1 = ::GetTickCount64(), time2 = ::GetTickCount64();
	Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\10bandman.gif"));
	Gdiplus::Image* backgroundimg2 = Image::FromFile(_T(".\\pic\\8bandman.gif"));
	Gdiplus::Image* lbnzimg = Image::FromFile(_T(".\\pic\\lbnz.gif"));
	Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome.gif"));
	Gdiplus::Image* shuaxinimg = Image::FromFile(_T(".\\pic\\刷新.png"));
	Gdiplus::Image* tiaoguoimg = Image::FromFile(_T(".\\pic\\跳过.gif"));
	Gdiplus::Image* jiuimg = Image::FromFile(_T(".\\pic\\酒桶编号.gif"));
	Gdiplus::Image* groupimg = Image::FromFile(_T(".\\pic\\group.gif"));
	Gdiplus::Image* img0999 = Image::FromFile(_T(".\\pic\\0999.gif"));
	Gdiplus::Image* img110 = Image::FromFile(_T(".\\pic\\1-10.gif"));

	CRect backhomerect;//主菜单
	CPoint backhomecen;
	CRect tiaoguorect;//跳过
	CPoint tiaoguocen;
	CRect shuaxinrect;//刷新
	CPoint shuaxincen;

	
	std::vector<BandMan*>bandmans;//奴隶10个
	std::vector<BandMan*>bandman8;//奴隶们8个
	std::vector<Image*>lnkr;//熊猫right
	std::vector<Image*>lnkl;//熊猫left
	std::vector<Image*>king;//国王
	std::vector<Image*>timeimg;//时间，，，，酒桶编号

	int poisonedwinenum = 0;
	bool to1000num = false;
	bool to250num = false;
	bool to31day = false;
	bool to5day = false;
	int posionedgroup = 0;//毒酒在第几组
	bool createrandom = true;

	PointF origin{ 0,7 };
	CString s;
	SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
	Gdiplus::Font m_font{ L"楷体",35.0,CFE_BOLD };    // 输出文字字体

	std::vector<int> binaryarr10;
	std::vector<int> binaryarr8;
	//int binaryarr[10] = { 0 };
	bool find = false;
	int nqian=0,nbai=0,nshi = 0, nge = 0;
	int  shi = 0, ge = 0;
	int ss= 0;
	int day =1;//第二个用

	float x = 0, y = 0, z = 0, p = 0;

	std::vector<Numberarr*>numimgarr;//0-9////数字集合
	std::vector<Numberarr*>numarr8;//问题二////数字集合
	//CPoint mousepoint;//鼠标位置
	ULONGLONG temptime31, temptime32, temptime33, temptime34 ;
	bool first31 = false, first32 = false, first33 = false, first34 = false;
	void init();//数据还原

	int bb = 0;

	void Choose(bool& inico1, bool& inico2, bool& inico3,Gdiplus::Graphics& gh);
	int RandomNumber();
	void drawpeop(Gdiplus::Graphics& gh);//画人物运动 头上标签  包括是否死亡等 
	void characterinit();
	void Draw(bool& inico1, bool& inico2, bool& inico3,int& gamestate, Gdiplus::Graphics& gh);
	double Theta(CPoint T, CPoint V);
	void TenBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh);

	void EightBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh);
};



