#pragma once
class MediaVoice:public Button
{
	public:
		MediaVoice(HWND hWnd);
		~MediaVoice();
		HWND m_hWnd;
		CRect m_rcClient;// �ͻ����Ĵ�С
		bool playmusic = true;
		Gdiplus::Image* voicekaiimg = Image::FromFile(_T(".\\pic\\voicekai.gif"));//��������ͼ��
		Gdiplus::Image* voiceguanimg = Image::FromFile(_T(".\\pic\\voiceguan.gif")); // �����ر�ͼ��
		void Draw(bool& inico, int& gamestate, Gdiplus::Graphics& gh);
		bool mediavoice = true;
};

