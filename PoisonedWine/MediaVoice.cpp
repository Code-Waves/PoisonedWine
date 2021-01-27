#include "pch.h"
#include "MediaVoice.h"
MediaVoice::MediaVoice(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd, &m_rcClient);
}
MediaVoice::~MediaVoice()
{
}
void MediaVoice::Draw(bool& inico, int& gamestate, Gdiplus::Graphics& gh)
{
    CRect voicerect{ m_rcClient.Width() - 140,m_rcClient.Height() - 70,(int)(voicekaiimg->GetWidth()),(int)(voicekaiimg->GetHeight()) };//about位置
    CPoint voicecen = rectCenter(voicerect);
    if (inRect(voicerect, mousepoint))
    {
        inico= true;
        /* if (GameState != inabout)
         GameState = invoice;*/
        if (mediavoice)
            gh.DrawImage(voicekaiimg, (voicecen.x - voicekaiimg->GetWidth() / 2 - 10), (voicecen.y - voicekaiimg->GetHeight() / 2 - 10), 70, 70);
        else
            gh.DrawImage(voiceguanimg, (voicecen.x - voicekaiimg->GetWidth() / 2 - 10), (voicecen.y - voicekaiimg->GetHeight() / 2 - 10), 70, 70);

        /*CString s(_T("音乐"));
        origin.X = voicerect.left - 33;
        origin.Y = voicerect.top - 22;
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);*/
    }
    else//鼠标未进入
    {
        inico= false;
        /*if (GameState != inabout)
            GameState = menu;*/
        if (mediavoice)
            gh.DrawImage(voicekaiimg, voicecen.x - voicekaiimg->GetWidth() / 2, voicecen.y - voicekaiimg->GetHeight() / 2, voicerect.right, voicerect.bottom);
        else
            gh.DrawImage(voiceguanimg, voicecen.x - voicekaiimg->GetWidth() / 2, voicecen.y - voicekaiimg->GetHeight() / 2, voicerect.right, voicerect.bottom);
    }
}


