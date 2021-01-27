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
    CString words = L"国王拥有一个酒窖,酒窖里面有一桶、两桶、三桶、四桶,共有一千桶酒。\r\n\r\n因为国王的恶毒与暴政遭到了神秘人的报复,\r\n\r\n神秘人在这一千桶酒中随机找了一桶酒下了毒药。\r\n\r\n毒药的毒性非常的猛烈,不论你如何进行稀释,\r\n\r\n微小的剂量都能让任何一个人在第三十天死亡。\r\n\r\n国王准备牺牲十个奴隶来找出毒酒,\r\n\r\n国王计划在三十五天之后举行一个宴会。\r\n\r\n你能否在宴会之前找出有毒的酒桶呢?\r\n\r\n又能否在只牺牲八个奴隶的情况下找出有毒的酒桶?";
    if (music)
        PlaySound(L".\\music\\read.wav", NULL, SND_ASYNC | SND_FILENAME);
    music = false;
    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());//背景

    //// 输出的文字
    wordindex++;
    CString s = words.Left(wordindex / 2.7);
    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

    //返回会主菜单
    CRect backhomerect{ m_rcClient.Width() - 230,m_rcClient.Height() - 80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    CPoint backhomecen = rectCenter(backhomerect);
    if (inRect(backhomerect, mousepoint))//鼠标进入
    {
        inico = true;
        backhome = true;
        gh.DrawImage(backhomeimg, (backhomecen.x - backhomeimg->GetWidth() / 2 - 10), (backhomecen.y - backhomeimg->GetHeight() / 2 -4), 220, 88);
    }
    else//鼠标未进入
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