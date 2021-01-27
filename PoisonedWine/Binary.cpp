#include "pch.h"
#include "Binary.h"

Binary::Binary(HWND hWnd)
{
    GetClientRect(hWnd, &m_rcClient);
    backhomerect = { 10,m_rcClient.Height() -80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    backhomecen = rectCenter(backhomerect);

    tiaoguorect = { m_rcClient.Width() -230,m_rcClient.Height() -80,(int)(backhomeimg->GetWidth()),(int)(backhomeimg->GetHeight()) };
    tiaoguocen = rectCenter(tiaoguorect);
}

void Binary::init()
{
    index1 = 0;
    index2 = 0;
    index3 = 0;
}

//跳过     主菜单
void Binary::Choose(bool& inico1, bool& inico2, Gdiplus::Graphics& gh)
{
    if (step < 3)
    {
        if (inRect(tiaoguorect, mousepoint))//跳过
        {
            inico1 = true;
            gh.DrawImage(tiaoguoimg, (tiaoguocen.x - tiaoguoimg->GetWidth() / 2 - 10), (tiaoguocen.y - tiaoguoimg->GetHeight() / 2 - 4), 220,88);
        }
        else//鼠标未进入
        {
            inico1 = false;
            gh.DrawImage(tiaoguoimg, tiaoguocen.x - tiaoguoimg->GetWidth() / 2, tiaoguocen.y - tiaoguoimg->GetHeight() / 2, tiaoguorect.right, tiaoguorect.bottom);
        }
  }
    ///
    
    if (inRect(backhomerect, mousepoint))//主菜单
    {
        inico2 = true;
        gh.DrawImage(backhomeimg, (backhomecen.x - backhomeimg->GetWidth() / 2 - 10), (backhomecen.y - backhomeimg->GetHeight() / 2 - 4), 220, 88);
    }
    else//鼠标未进入
    {
        inico2 = false;
        gh.DrawImage(backhomeimg, backhomecen.x - backhomeimg->GetWidth() / 2, backhomecen.y - backhomeimg->GetHeight() / 2, backhomerect.right, backhomerect.bottom);
    }

}

void Binary::DrawBandmans(int &k, int &exchange,std::vector<BandMan*> bandmans, Gdiplus::Graphics& gh)
{
    k++;
    if (k % 7 == 1)
    {
        exchange = exchange == 1 ? 0 : 1;
    }

    for (int i = 0; i < bandmans.size(); i++)
    {
        gh.DrawImage(bandmans[i]->character[exchange], bandmans[i]->place.left, bandmans[i]->place.top, 70, 70);
    }
    if (k > 7000000)k = 1;
}

void Binary::Draw(bool& inico1, bool& inico2, int& gamestate,std::vector<BandMan*>bandmans, Gdiplus::Graphics& gh)
{
    if (step == 1)
    {
        bofang2 = true;
        Binarymess(inico1, inico2, gh, bandmans);
    }
    else if (step == 2)
    {   
        bofang1 = true;
        bofang3 = true;
        TentoBinary(inico1, inico2, gh, bandmans);
    }
    else if (step == 3)
    {
        bofang2 = true;
        BinarytoTen(inico1, inico2, gh, bandmans);
    }
}

//二进制介绍
void Binary::Binarymess(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*>bandmans)
{
    CString words = L"\r\n我们先要知道一个概念,就是二进制,\r\n\r\n二进制由来已久,最早是可以追溯到五百年前的。\r\n\r\n我们日常的生活当中,数字都是十进制的,比如数字12，\r\n\r\n但是在二进制当中,使用0和1两个数字来表示的数,\r\n\r\n它的基数是2,进位规则也显而易见,“逢二进一”,\r\n\r\n这种运算方式最初由18世纪德国数理哲学大师莱布尼兹发现的,\r\n\r\n有了这个方法以后,我们如何将日常的十进制数字转化成二进制呢?";
    if (bofang1)
    {
        PlaySound(L".\\music\\二进制起源.wav", NULL, SND_ASYNC | SND_FILENAME);
        time1 = GetTickCount64();
    }
    bofang1 = false;

    gh.DrawImage(backgroundimg, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());

    if (::GetTickCount64() - time1 > 24000 && ::GetTickCount64() - time1 < 34000)
        gh.DrawImage(lbnzimg, 0, 150, lbnzimg->GetWidth(), lbnzimg->GetHeight());

    if (::GetTickCount64() - time1 > 36000)step++;

    PointF origin{ 250.0f,0.0f };
    SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体",16.0,CFE_BOLD };    // 输出文字字体
    //// 输出的文字

    index1++;
    CString s = words.Left(index1 /su);

    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
    static int k = 0, exchange = 0;

    DrawBandmans(k, exchange, bandmans, gh);

    Choose(inico1, inico2, gh);
}
//十进制转二进制
void Binary::TentoBinary(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*>bandmans)
{

    CString words = L"\r\n比如说对于数字12,我们可以利用除法,\r\n\r\n将十进制的12除以2,得到的商为6,余数为0。\r\n\r\n进一步我们拿6÷2得到商是3,余数是0,\r\n\r\n再将3除以2,得到商是1,余数为1,\r\n\r\n直到商为0的时候,我们的除法就结束。\r\n\r\n然后我们从最后的位置开始将余数组合在一起,\r\n\r\n从下往上就得到了我们的二进制数1100就是12的十进制数的二进制表达方式,\r\n\r\n那我们如何将二进制数字转化成十进制呢?\r\n";
    CString jisuan = L"12  ÷  2  =  6••••••0\r\n6   ÷  2  =  3••••••0\r\n3   ÷  2  =  1••••••1\r\n1   ÷  2  =  0••••••1\r\n   1   1   0   0";

    if (bofang2)
    {
        kk = 0;
        time2 = GetTickCount64();
        PlaySound(L".\\music\\十进制转二进制.wav", NULL, SND_ASYNC | SND_FILENAME);
    }
    bofang2 = false;

    gh.DrawImage(backgroundimg4, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
  
    /* if (::GetTickCount64() - dwLast > 24000 && ::GetTickCount64() - dwLast < 34000)
         gh.DrawImage(lbnzimg, 0, 190, lbnzimg->GetWidth(), lbnzimg->GetHeight());*/

    if (::GetTickCount64() - time2 > 38000)step++;

    SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体",14.0,CFE_BOLD };    // 输出文字字体
    //// 输出的文字
    index2++; 
    CString s = words.Left(index2 /su);
    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

    CString t;
    if (::GetTickCount64() - time2 > 6000) 
    {
        if (kk <406)
            kk += 1;
        Rect rect{580,0,666,kk};
        gh.DrawImage(stoe, rect, 0, 0, 666,kk, UnitPixel);
    }

    Gdiplus::Font m_font1{ L"楷体",22.0,CFE_BOLD };    // 输出文字字体
    SolidBrush m_brush1{ Color::Red };// 输出FPS文字用的画刷
    gh.DrawString(t.GetString(), -1, &m_font1, origin1, &m_brush1);

    static int k = 0, exchange = 0;

    DrawBandmans(k, exchange, bandmans, gh);

    Choose(inico1, inico2, gh);
}
//二进制转十进制
void Binary::BinarytoTen(bool& inico1, bool& inico2, Gdiplus::Graphics& gh, std::vector<BandMan*>bandmans)
{
    CString words = L"\r\n比如对于二进制数字1100如何转换成十进制数呢?\r\n\r\n首先对于第一位的1,1的后面有三位，我们就拿1乘以2³,\r\n\r\n第二位1,1的后面有两位,就拿1乘以2²,\r\n\r\n第三位数字0,0的数字后面有一位,我们就拿0乘以2¹,\r\n\r\n最后一位0,0的数字后面没有数字,我们就拿0乘以2⁰,\r\n\r\n将前面得到的结果相加,我们就得到了二进制1100的十进制数12";
    //CString jisuan = L"1   ×   2³   =   8\r\n1   ×   2²   =   4\r\n0   ×   2¹   =   0\r\n0   ×   2⁰   =   0\r\n8 + 4 + 0 + 0 =  12";
    if (bofang3)
    {
        kk = 0;
        time3 = GetTickCount64();
        PlaySound(L".\\music\\二进制转十进制.wav", NULL, SND_ASYNC | SND_FILENAME);
    }
    bofang3= false;

    gh.DrawImage(backgroundimg5, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());


    SolidBrush m_brush{ Color::Black };// 输出FPS文字用的画刷
    Gdiplus::Font m_font{ L"楷体",16.0,CFE_BOLD };    // 输出文字字体
    //// 输出的文字
    index3++;
    CString s = words.Left(index3 / su);
    gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);

    CString t;
    if (::GetTickCount64() - time3 > 7000)
    {
        if (kk < 406)
            kk += 1;
        Rect rect{ 680,0,666,kk };
        gh.DrawImage(etos, rect, 0, 0, 666, kk, UnitPixel);
    }

    Gdiplus::Font m_font1{ L"楷体",22.0,CFE_BOLD };    // 输出文字字体
    SolidBrush m_brush1{ Color::Red };// 输出FPS文字用的画刷
   

    static int k = 0, exchange = 0;

    DrawBandmans(k, exchange, bandmans, gh);

    Choose(inico1, inico2, gh);
}













