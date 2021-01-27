#pragma once
class MediaVoice:public Button
{
	public:
		MediaVoice(HWND hWnd);
		~MediaVoice();
		HWND m_hWnd;
		CRect m_rcClient;// 客户区的大小
		bool playmusic = true;
		Gdiplus::Image* voicekaiimg = Image::FromFile(_T(".\\pic\\voicekai.gif"));//声音开启图标
		Gdiplus::Image* voiceguanimg = Image::FromFile(_T(".\\pic\\voiceguan.gif")); // 声音关闭图标
		void Draw(bool& inico, int& gamestate, Gdiplus::Graphics& gh);
		bool mediavoice = true;
};

