#pragma once
//#include"Button.h"
class FrontNextMusic :public Button
{
public:
	FrontNextMusic(HWND hWnd);
	~FrontNextMusic();
	HWND m_hWnd;
	CRect m_rcClient;// 客户区的大小
	int setangel = 35;//所有唱针旋转最大角
	int stylusAngel = 0;//唱针旋转角度
	int clickChangeMusicAngel = setangel;//点击切换音乐  唱针来回运动的角度变化
	bool runonce = false;//换music时 唱针来回运动一次  是否已经回到初始点  回到了角度++回来  没有则--
	int frontimgindex = 0;//记录点击上下一曲时  此时图片索引
	std::vector<CString>MusicPath;
	std::vector<Image*>nodeimg;//音符
	bool clickchangemusic = false;//是否点击了上一曲下一曲
	int longplayingAngel = 0;//黑胶唱片动态旋转角度  随时改变
	std::vector<Image*> LongPlayingimg;//黑胶唱片图片数组
	int LongPlayingimgindex = 0;//黑胶唱片以及对应音乐的索引
	Gdiplus::Image* frontimg = Image::FromFile(_T(".\\pic\\shangyiqu.gif")); //上一曲图标
	Gdiplus::Image* nextimg = Image::FromFile(_T(".\\pic\\xiayiqu.gif")); // 下一曲图标
	void Draw(bool& infrontico, bool& innextico, int& gamestate, Gdiplus::Graphics& gh);

	void MusicimgDance(Gdiplus::Graphics& gh, bool& mediavoice, bool& playmusic);

	void RotateLongPlaying(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice);

	void RotateStylus(Gdiplus::Graphics& gh, CRect musicrect, bool& mediavoice, bool& playmusic, REAL x =190, REAL y =460);

	void NodeDance(Gdiplus::Graphics& gh);

};

