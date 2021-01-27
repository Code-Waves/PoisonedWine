#include "pch.h"
#include "Story.h"
Story::Story(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd, &m_rcClient);
}

Story::~Story()
{
}

void Story::Draw(bool& inico, std::vector<BandMan*>bandmans, Gdiplus::Graphics& gh)
{
    CString words = L"����ӵ��һ���ƽ�,�ƽ�������һͰ����Ͱ����Ͱ����Ͱ,����һǧͰ�ơ�\r\n\r\n��Ϊ�����Ķ��뱩���⵽�������˵ı���,\r\n\r\n����������һǧͰ�����������һͰ�����˶�ҩ��\r\n\r\n��ҩ�Ķ��Էǳ�������,��������ν���ϡ��,\r\n\r\n΢С�ļ����������κ�һ�����ڵ���ʮ��������\r\n\r\n����׼������ʮ��ū�����ҳ�����,\r\n\r\n�����ƻ�����ʮ����֮�����һ����ᡣ\r\n\r\n���ܷ������֮ǰ�ҳ��ж��ľ�Ͱ��?\r\n\r\n���ܷ���ֻ�����˸�ū����������ҳ��ж��ľ�Ͱ?";
    if (music)
        PlaySound(L".\\music\\read.wav", NULL, SND_ASYNC | SND_FILENAME);
    music = false;
    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());//����

    //// ���������
    wordindex++;
    CString s = words.Left(wordindex / 2.7);
    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

    //���ػ����˵�
    CRect backhomerect{ m_rcClient.Width() - 230,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    CPoint backhomecen = rectCenter(backhomerect);
    if (inRect(backhomerect, mousepoint))//������
    {
        inico = true;
        backhome = true;
        gh.DrawImage(backhomeimg, (backhomecen.x - backhomeimg->GetWidth() / 2 - 10), (backhomecen.y - backhomeimg->GetHeight() / 2 -4), 220, 88);
    }
    else//���δ����
    {
        inico = false;
        gh.DrawImage(backhomeimg, backhomecen.x - backhomeimg->GetWidth() / 2, backhomecen.y - backhomeimg->GetHeight() / 2, backhomerect.right, backhomerect.bottom);
    }
     static int k = 0, bb = 0;
     k++;
     if (k % 7 == 1)
     {
         bb = bb == 1 ? 0 : 1;
     }

     for (int i = 0; i < bandmans.size(); i++)
     {
         gh.DrawImage(bandmans[i]->character[bb], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
     }
     if (k > 7000000)k = 1;
}