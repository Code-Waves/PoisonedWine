#include "pch.h"
#include "OtherFuction.h"
OtherFuction::OtherFuction(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd, &m_rcClient);
    rackmusicpath = L".\\music\\rockstar.wav";
}

OtherFuction::~OtherFuction()
{
}
void OtherFuction::Start(bool& inico, int& gamestate, Gdiplus::Graphics& gh)
{
    CRect otherrect{ m_rcClient.Width() - 350,m_rcClient.Height() - 70,(int)(otherimg->GetWidth()),(int)(otherimg->GetHeight()) };//about位置
    CPoint othercen = rectCenter(otherrect);
    if (inRect(otherrect, mousepoint))
    {
        inico= true;
        
        gh.DrawImage(otherimg, (othercen.x - otherimg->GetWidth() / 2 - 6), (othercen.y - otherimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//鼠标未进入
    {
        inico= false;
        gamestate = menu;
        gh.DrawImage(otherimg, othercen.x - otherimg->GetWidth() / 2, othercen.y - otherimg->GetHeight() / 2, otherrect.right, otherrect.bottom);
    }
    static int i = 0;
    if (fire)//满足起飞条件
    {
        CRect rockbottomrect{ (int)(m_rcClient.Width() / 2 - rockbottomimg->GetWidth() / 2),m_rcClient.Height() - 73,(int)(rockbottomimg->GetWidth()),(int)(rockbottomimg->GetHeight()) };//about位置
        CPoint rockbottomcen = rectCenter(rockbottomrect);
        gh.DrawImage(rackstarimg, rockbottomcen.x - rackstarimg->GetWidth() / 2, rockbottomcen.y - 100 - rockheight, rockbottomrect.bottom, rockbottomrect.right);
        gh.DrawImage(rockbottomimg, rockbottomrect.left, rockbottomrect.top, rockbottomimg->GetWidth(), rockbottomimg->GetHeight());
        i++;
        rockheight =i*i*5;
        if (rockheight > m_rcClient.Height() * 2)
        {
            fire = false;
        }
    }
    else
    {
        i = 0;
        rockheight = 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////火箭
}