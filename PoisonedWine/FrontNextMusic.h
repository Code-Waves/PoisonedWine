#pragma once
//#include"Button.h"
class FrontNextMusic :public Button
{
public:
	FrontNextMusic(HWND hWnd);
	~FrontNextMusic();
	HWND m_hWnd;
	CRect m_rcClient;// �ͻ����Ĵ�С
	int setangel = 35;//���г�����ת����
	int stylusAngel = 0;//������ת�Ƕ�
	int clickChangeMusicAngel = setangel;//����л�����  ���������˶��ĽǶȱ仯
	bool runonce = false;//��musicʱ ���������˶�һ��  �Ƿ��Ѿ��ص���ʼ��  �ص��˽Ƕ�++����  û����--
	int frontimgindex = 0;//��¼�������һ��ʱ  ��ʱͼƬ����
	std::vector<CString>MusicPath;
	std::vector<Image*>nodeimg;//����
	bool clickchangemusic = false;//�Ƿ�������һ����һ��
	int longplayingAngel = 0;//�ڽ���Ƭ��̬��ת�Ƕ�  ��ʱ�ı�
	std::vector<Image*> LongPlayingimg;//�ڽ���ƬͼƬ����
	int LongPlayingimgindex = 0;//�ڽ���Ƭ�Լ���Ӧ���ֵ�����
	Gdiplus::Image* frontimg = Image::FromFile(_T(".\\pic\\shangyiqu.gif")); //��һ��ͼ��
	Gdiplus::Image* nextimg = Image::FromFile(_T(".\\pic\\xiayiqu.gif")); // ��һ��ͼ��
	void Draw(bool& infrontico, bool& innextico, int& gamestate, Gdiplus::Graphics& gh);

	void MusicimgDance(Gdiplus::Graphics& gh, bool& mediavoice, bool& playmusic);

	void RotateLongPlaying(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice);

	void RotateStylus(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice, bool& playmusic, REAL x =190, REAL y =460);

	void NodeDance(Gdiplus::Graphics& gh);

};

