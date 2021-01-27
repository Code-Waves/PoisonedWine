#include "pch.h"
#include "StoryorPro.h"
StoryorPro::StoryorPro(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd, &m_rcClient);
    storyorpro.push_back(Image::FromFile(_T(".\\pic\\¹ÊÊÂ±³¾°.gif")));
    storyorpro.push_back(Image::FromFile(_T(".\\pic\\Ëã·¨ÑÝÊ¾.gif")));
}

StoryorPro::~StoryorPro()
{
}
void StoryorPro::Draw(bool& instoryico, bool& inproico, int& gamestate, Gdiplus::Graphics& gh)
{
    /* gh.DrawImage(gsbjimg, 200,m_rcClient.Height()/2-gsbjimg->GetHeight()/2);
    gh.DrawImage(sfysimg,(int)(m_rcClient.right-200-sfysimg->GetWidth()), (m_rcClient.Height() / 2 - sfysimg->GetHeight() / 2));*/
    CRect storyrect { 150,(int) (m_rcClient.Height() / 2 - gsbjimg->GetHeight() / 2), (int)storyorpro[0] ->GetWidth(), (int)storyorpro[0] ->GetHeight()};
    CRect prorect{ (int)(m_rcClient.right - 150 - sfysimg->GetWidth()),  (int)(m_rcClient.Height() / 2 - sfysimg->GetHeight() / 2) , (int)(storyorpro[1]->GetWidth()), (int)storyorpro[1]->GetHeight() };
    CPoint storycen = rectCenter(storyrect);
    CPoint procen = rectCenter(prorect);

    if (inRect(storyrect, mousepoint))
    {
        instoryico = true;
        gh.DrawImage(storyorpro[0], (storycen.x - storyorpro[0]->GetWidth() / 2 - 20), (storycen.y - storyorpro[0]->GetHeight() / 2 - 105),170, 390);
        gh.DrawImage(storyorpro[1], (int)(m_rcClient.right - 150 - sfysimg->GetWidth()), (int)(m_rcClient.Height() / 2 - sfysimg->GetHeight() / 2) - 60);
    }
    else if(inRect(prorect, mousepoint))
    {
        inproico = true;
        gh.DrawImage(storyorpro[0], 150, m_rcClient.Height() / 2 - storyorpro[0]->GetHeight() / 2 - 60);
        gh.DrawImage(storyorpro[1], (procen.x - storyorpro[1]->GetWidth() / 2 -20 ), (procen.y - storyorpro[1]->GetHeight() / 2 - 105), 170, 390);
    }
    else
    {
        gh.DrawImage(storyorpro[0], 150, m_rcClient.Height() / 2 - storyorpro[0]->GetHeight() / 2-60);
        gh.DrawImage(storyorpro[1], (int)(m_rcClient.right - 150 - storyorpro[1]->GetWidth()), (int)(m_rcClient.Height() / 2 - storyorpro[1]->GetHeight() / 2) - 60);
        instoryico = false;
        inproico = false;
    }
}
