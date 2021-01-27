#pragma once
class Principle:public Button
{
public:
	int state = 1;
	PointF origin{ 250,0 };
	PointF origin1{ 250,270 };
	Principle(HWND hWnd);
	CRect m_rcClient;
	int su =3.9;
	int index1 = 0, index2 = 0, index3 = 0 ;
	bool bofang1 = true, bofang2 = true, bofang3 = true;
	ULONGLONG time1, time2, time3;
	Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\background3.gif"));
	Gdiplus::Image* lbnzimg = Image::FromFile(_T(".\\pic\\lbnz.gif"));
	Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome.gif"));
	Gdiplus::Image* tiaoguoimg = Image::FromFile(_T(".\\pic\\跳过.gif"));
	CRect backhomerect;//主菜单
	CPoint backhomecen;
	CRect tiaoguorect;//跳过
	CPoint tiaoguocen;

	//CPoint mousepoint;//鼠标位置

	void init();

	void Ico(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);

	void Draw(bool& inico1, bool& inico2, int& gamestate,/* CPoint mousepoint, */std::vector<BandMan*> bandmans, Gdiplus::Graphics& gh);
	void Binarymess(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	void TentoBinary(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	void BinarytoTen(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	/*bool inRect(CRect rc, CPoint mouse);
	CPoint rectCenter(CRect rc);*/
};

