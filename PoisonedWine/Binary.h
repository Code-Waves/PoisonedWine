#pragma once
class Binary:public Button
{
public:
	int step = 1;
	int kk = 0;
	PointF origin{ 0,20 };
	PointF origin1{ 650,100 };
	Binary(HWND hWnd);
	CRect m_rcClient;
	float su =2.5;
	int index1 = 0, index2 = 0, index3 = 0 ;
	bool bofang1 = true, bofang2 = true, bofang3 = true,bofang4=true;
	ULONGLONG time1, time2, time3, time4;
	Gdiplus::Image* backgroundimg = Image::FromFile(_T(".\\pic\\background3.gif"));
	Gdiplus::Image* backgroundimg4 = Image::FromFile(_T(".\\pic\\background4.gif"));
	Gdiplus::Image* backgroundimg5 = Image::FromFile(_T(".\\pic\\background5.gif"));
	Gdiplus::Image* lbnzimg = Image::FromFile(_T(".\\pic\\lbnz.gif"));
	Gdiplus::Image* backhomeimg = Image::FromFile(_T(".\\pic\\backhome.gif"));
	Gdiplus::Image* tiaoguoimg = Image::FromFile(_T(".\\pic\\跳过.gif"));
	Gdiplus::Image* etos = Image::FromFile(_T(".\\pic\\2to10.png"));
	Gdiplus::Image* stoe = Image::FromFile(_T(".\\pic\\10to2.png"));
	CRect backhomerect;//主菜单
	CPoint backhomecen;
	CRect tiaoguorect;//跳过
	CPoint tiaoguocen; 

	//CPoint mousepoint;//鼠标位置

	void init();

	void Choose(bool& inico1, bool& inico2, Gdiplus::Graphics& gh);

	void DrawBandmans(int& k, int& exchange,std::vector<BandMan*> bandmans, Gdiplus::Graphics& gh);

	void Draw(bool& inico1, bool& inico2, int& gamestate,std::vector<BandMan*> bandmans, Gdiplus::Graphics& gh);
	void Binarymess(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	void TentoBinary(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	void BinarytoTen(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*> bandmans);
	/*bool inRect(CRect rc, CPoint mouse);
	CPoint rectCenter(CRect rc);*/
};

