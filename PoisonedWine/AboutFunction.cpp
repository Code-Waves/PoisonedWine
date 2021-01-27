#include "pch.h"
#include "AboutFunction.h"
AboutFunction::AboutFunction(HWND hWnd)
    : m_hWnd(hWnd)
{
    GetClientRect(m_hWnd,&m_rcClient);
}

AboutFunction::~AboutFunction()
{
}
void AboutFunction::Draw(bool &inico,int &gamestate,Gdiplus::Graphics& gh)
{
    CRect aboutrect{ m_rcClient.Width() - 70,m_rcClient.Height() - 70,(int)(aboutimg->GetWidth()),(int)(aboutimg->GetHeight()) };//about位置
    CPoint aboutcen = rectCenter(aboutrect);
    if (inRect(aboutrect, mousepoint))//鼠标进入about
    {
        inico = true;
        gh.DrawImage(aboutimg, (aboutcen.x - aboutimg->GetWidth() / 2 - 6), (aboutcen.y - aboutimg->GetHeight() / 2 - 6), 70, 70);
    }
    else//鼠标未进入
    {
        inico = false;
        gamestate =menu;
        gh.DrawImage(aboutimg, aboutcen.x - aboutimg->GetWidth() / 2, aboutcen.y - aboutimg->GetHeight() / 2, aboutrect.right, aboutrect.bottom);

    }
}

void AboutFunction::Drawbackground(Gdiplus::Graphics& gh)
{
    static int e = 0;
    e+=40;
    gh.TranslateTransform(551,283);
    gh.RotateTransform(e);
    gh.DrawImage(round,-283,-283, 566, 566);
    gh.ResetTransform();//还原
    if (e > 360)e = 40;
    gh.DrawImage(application, 338, 127, 425, 315);
}



