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
	void toZero();//����������֮ǰ   �ȹ���
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
	Gdiplus::Image* shuaxinimg = Image::FromFile(_T(".\\pic\\ˢ��.png"));
	Gdiplus::Image* tiaoguoimg = Image::FromFile(_T(".\\pic\\����.gif"));
	Gdiplus::Image* jiuimg = Image::FromFile(_T(".\\pic\\��Ͱ���.gif"));
	Gdiplus::Image* groupimg = Image::FromFile(_T(".\\pic\\group.gif"));
	Gdiplus::Image* img0999 = Image::FromFile(_T(".\\pic\\0999.gif"));
	Gdiplus::Image* img110 = Image::FromFile(_T(".\\pic\\1-10.gif"));

	CRect backhomerect;//���˵�
	CPoint backhomecen;
	CRect tiaoguorect;//����
	CPoint tiaoguocen;
	CRect shuaxinrect;//ˢ��
	CPoint shuaxincen;

	
	std::vector<BandMan*>bandmans;//ū��10��
	std::vector<BandMan*>bandman8;//ū����8��
	std::vector<Image*>lnkr;//��èright
	std::vector<Image*>lnkl;//��èleft
	std::vector<Image*>king;//����
	std::vector<Image*>timeimg;//ʱ�䣬��������Ͱ���

	int poisonedwinenum = 0;
	bool to1000num = false;
	bool to250num = false;
	bool to31day = false;
	bool to5day = false;
	int posionedgroup = 0;//�����ڵڼ���
	bool createrandom = true;

	PointF origin{ 0,7 };
	CString s;
	SolidBrush m_brush{ Color::Black };// ���FPS�����õĻ�ˢ
	Gdiplus::Font m_font{ L"����",35.0,CFE_BOLD };    // �����������

	std::vector<int> binaryarr10;
	std::vector<int> binaryarr8;
	//int binaryarr[10] = { 0 };
	bool find = false;
	int nqian=0,nbai=0,nshi = 0, nge = 0;
	int  shi = 0, ge = 0;
	int ss= 0;
	int day =1;//�ڶ�����

	float x = 0, y = 0, z = 0, p = 0;

	std::vector<Numberarr*>numimgarr;//0-9////���ּ���
	std::vector<Numberarr*>numarr8;//�����////���ּ���
	//CPoint mousepoint;//���λ��
	ULONGLONG temptime31, temptime32, temptime33, temptime34 ;
	bool first31 = false, first32 = false, first33 = false, first34 = false;
	void init();//���ݻ�ԭ

	int bb = 0;

	void Choose(bool& inico1, bool& inico2, bool& inico3,Gdiplus::Graphics& gh);
	int RandomNumber();
	void drawpeop(Gdiplus::Graphics& gh);//�������˶� ͷ�ϱ�ǩ  �����Ƿ������� 
	void characterinit();
	void Draw(bool& inico1, bool& inico2, bool& inico3,int& gamestate, Gdiplus::Graphics& gh);
	double Theta(CPoint T, CPoint V);
	void TenBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh);

	void EightBandMan(bool& inico1, bool& inico2, bool& inico3, Gdiplus::Graphics& gh);
};



